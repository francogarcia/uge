/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "ScriptExports.h"
#include "ScriptEvent.h"
#include "LuaStateManager.h"

#include <Utilities/Debug/Logger.h>
#include <Core/Events/DefaultEvents.h>
#include <Core/Resource/ResourceCache.h>
#include <Core/Task/Task.h>

// FIXME / XXX: Refactor this and remove globals.
#include <Engine/GameApplication/GameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

namespace uge
{

    //---------------------------------------------------------------------------------------------------------------------
    // This is the C++ listener proxy for script event listeners.  It pairs a single event type with a Lua callback
    // function.  Note that this event can be defined in C++ or Lua.  It may also be sent from C++ or Lua.
    //
    // The Lua callback function should take in a table with the event data.  The return value is ignored.
    // function Callback(eventData)
    //
    // Chapter 12, page 384
    //---------------------------------------------------------------------------------------------------------------------
    class ScriptEventListener
    {
    public:
        explicit ScriptEventListener(const EventType& eventType, const LuaPlus::LuaObject& scriptCallbackFunction);
        ~ScriptEventListener();
        EventListenerDelegate GetDelegate()
        {
            return fastdelegate::MakeDelegate(this, &ScriptEventListener::ScriptEventDelegate);
        }
        void ScriptEventDelegate(IEventDataSharedPointer pEventPtr);

    private:
        EventType m_EventType;
        LuaPlus::LuaObject m_ScriptCallbackFunction;
    };


    //---------------------------------------------------------------------------------------------------------------------
    // This class manages the C++ ScriptListener objects needed for script event listeners.
    // Chapter 12, page 385
    //---------------------------------------------------------------------------------------------------------------------
    class ScriptEventListenerMgr
    {
    public:
        ~ScriptEventListenerMgr();
        void AddListener(ScriptEventListener* pListener);
        void DestroyListener(ScriptEventListener* pListener);

    private:
        typedef std::set<ScriptEventListener*> ScriptEventListenerSet;
        ScriptEventListenerSet m_Listeners;
    };


    //---------------------------------------------------------------------------------------------------------------------
    // Prototypes for the functions to export.                              - Chapter 12, page 368
    //---------------------------------------------------------------------------------------------------------------------
    class InternalScriptExports
    {
    public:
        // initialization
        static bool Init();
        static void Destroy();

        // resource loading
        static bool LoadAndExecuteScriptResource(const char* pScriptResource);

        // actors
        static int CreateActor(const char* pActorArchetype, LuaPlus::LuaObject luaPosition, LuaPlus::LuaObject luaYawPitchRoll);

        // event system
        static unsigned long RegisterEventListener(EventType eventType, LuaPlus::LuaObject callbackFunction);
        static void RemoveEventListener(unsigned long listenerId);
        static bool QueueEvent(EventType eventType, LuaPlus::LuaObject eventData);
        static bool TriggerEvent(EventType eventType, LuaPlus::LuaObject eventData);

        // process system
        static void AttachScriptTask(LuaPlus::LuaObject scriptTask);

        // math
        static float GetYRotationFromVector(LuaPlus::LuaObject vec3);
        static float WrapPi(float wrapMe);
        static LuaPlus::LuaObject GetVectorFromRotation(float angleRadians);

        // misc
        static void LuaLog(LuaPlus::LuaObject text);
        static unsigned long GetTickCount();

        // physics
        static void ApplyForce(LuaPlus::LuaObject normalDir, float force, int actorId);
        static void ApplyTorque(LuaPlus::LuaObject axis, float force, int actorId);

    private:
        static std::shared_ptr<ScriptEvent> BuildEvent(EventType eventType, LuaPlus::LuaObject& eventData);

        static ScriptEventListenerMgr* s_pScriptEventListenerMgr;
    };

    ScriptEventListenerMgr* InternalScriptExports::s_pScriptEventListenerMgr = nullptr;

    //---------------------------------------------------------------------------------------------------------------------
    // Destructor
    //---------------------------------------------------------------------------------------------------------------------
    ScriptEventListenerMgr::~ScriptEventListenerMgr()
    {
        for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
        {
            ScriptEventListener* pListener = (*it);
            delete pListener;
        }
        m_Listeners.clear();
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Adds a new listener
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptEventListenerMgr::AddListener(ScriptEventListener* pListener)
    {
        m_Listeners.insert(pListener);
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Destroys a listener
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptEventListenerMgr::DestroyListener(ScriptEventListener* pListener)
    {
        ScriptEventListenerSet::iterator findIt = m_Listeners.find(pListener);
        if (findIt != m_Listeners.end())
        {
            m_Listeners.erase(findIt);
            delete pListener;
        }
        else
        {
            LOG_ERROR("Couldn't find script listener in set; this will probably cause a memory leak");
        }
    }


    //---------------------------------------------------------------------------------------------------------------------
    // Event Listener
    //---------------------------------------------------------------------------------------------------------------------
    ScriptEventListener::ScriptEventListener(const EventType& eventType, const LuaPlus::LuaObject& scriptCallbackFunction)
        :   m_ScriptCallbackFunction(scriptCallbackFunction)
    {
        m_EventType = eventType;
    }

    ScriptEventListener::~ScriptEventListener()
    {
        IEventManager* pEventMgr = IEventManager::Get();
        if (pEventMgr)
        {
            pEventMgr->vRemoveListener(GetDelegate(), m_EventType);
        }
    }

    void ScriptEventListener::ScriptEventDelegate(IEventDataSharedPointer pEvent)
    {
        assert(m_ScriptCallbackFunction.IsFunction() && "Invalid callbak is not a function!");  // this should never happen since it's validated before even creating this object

        // call the Lua function
        std::shared_ptr<ScriptEvent> pScriptEvent = std::static_pointer_cast<ScriptEvent>(pEvent);
        LuaPlus::LuaFunction<void> Callback = m_ScriptCallbackFunction;
        Callback(pScriptEvent->GetEventData());
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Initializes the script export system
    //---------------------------------------------------------------------------------------------------------------------
    bool InternalScriptExports::Init()
    {
        assert((s_pScriptEventListenerMgr == nullptr) && "The event listener was already initialized!");
        s_pScriptEventListenerMgr = LIB_NEW ScriptEventListenerMgr;

        return true;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Destroys the script export system
    //---------------------------------------------------------------------------------------------------------------------
    void InternalScriptExports::Destroy()
    {
        assert((s_pScriptEventListenerMgr != nullptr) && "The event listener was not initialized!");
        SAFE_DELETE(s_pScriptEventListenerMgr);
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Loads a script resource then executes it.  This is used by the require() function in script (defined in
    // PreInit.lua).
    //---------------------------------------------------------------------------------------------------------------------
    bool InternalScriptExports::LoadAndExecuteScriptResource(const char* pScriptResource)
    {
        if (!g_pApp->vGetResourceCache()->IsUsingDevelopmentDirectories())
        {
            Resource resource(pScriptResource);
            ResourceHandleSharedPointer pResourceHandle = g_pApp->vGetResourceCache()->GetHandle(&resource);  // this actually loads the Lua file from the zip file
            if (pResourceHandle != nullptr)
            {
                return true;
            }

            return false;
        }
        else
        {
            // If we're using development directories, have Lua execute the file directly instead of going through
            // the resource cache.  This allows Decoda to see the file for debugging purposes.
            std::string path("..\\Assets\\");
            path += pScriptResource;
            LuaStateManager::Get()->vExecuteFile(path.c_str());
            return true;
        }
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Instantiates a C++ ScriptListener object, inserts it into the manager, and returns a handle to it.  The script
    // should maintain the handle if it needs to remove the listener at some point.  Otherwise, the listener will be
    // destroyed when the program exits.
    //---------------------------------------------------------------------------------------------------------------------
    unsigned long InternalScriptExports::RegisterEventListener(EventType eventType, LuaPlus::LuaObject callbackFunction)
    {
        assert(s_pScriptEventListenerMgr);

        if (callbackFunction.IsFunction())
        {
            // create the C++ listener proxy and set it to listen for the event
            ScriptEventListener* pListener = LIB_NEW ScriptEventListener(eventType, callbackFunction);
            s_pScriptEventListenerMgr->AddListener(pListener);
            IEventManager::Get()->vAddListener(pListener->GetDelegate(), eventType);

            // convert the pointer to an unsigned long to use as the handle
            unsigned long pHandle = reinterpret_cast<unsigned long>(pListener);
            return pHandle;
        }

        LOG_ERROR("Attempting to register script event listener with invalid callback function");
        return 0;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Removes a script listener.
    //---------------------------------------------------------------------------------------------------------------------
    void InternalScriptExports::RemoveEventListener(unsigned long listenerId)
    {
        assert(s_pScriptEventListenerMgr && "The event listener was not initialized!");
        assert((listenerId != 0) && "Invalid listener ID!");

        // convert the listenerId back into a pointer
        ScriptEventListener* pListener = reinterpret_cast<ScriptEventListener*>(listenerId);
        s_pScriptEventListenerMgr->DestroyListener(pListener);  // the destructor will remove the listener
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Queue's an event from the script.  Returns true if the event was sent, false if not.
    //---------------------------------------------------------------------------------------------------------------------
    bool InternalScriptExports::QueueEvent(EventType eventType, LuaPlus::LuaObject eventData)
    {
        std::shared_ptr<ScriptEvent> pEvent(BuildEvent(eventType, eventData));
        if (pEvent)
        {
            IEventManager::Get()->vQueueEvent(pEvent);
            return true;
        }
        return false;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Sends an event from the script.  Returns true if the event was sent, false if not.
    //---------------------------------------------------------------------------------------------------------------------
    bool InternalScriptExports::TriggerEvent(EventType eventType, LuaPlus::LuaObject eventData)
    {
        std::shared_ptr<ScriptEvent> pEvent(BuildEvent(eventType, eventData));
        if (pEvent)
        {
            return IEventManager::Get()->vTriggerEvent(pEvent);
        }
        return false;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // Builds the event to be sent or queued
    //---------------------------------------------------------------------------------------------------------------------
    std::shared_ptr<ScriptEvent> InternalScriptExports::BuildEvent(EventType eventType, LuaPlus::LuaObject& eventData)
    {
        // create the event from the event type
        std::shared_ptr<ScriptEvent> pEvent(ScriptEvent::CreateEventFromScript(eventType));
        if (!pEvent)
        {
            return std::shared_ptr<ScriptEvent>();
        }

        // set the event data that was passed in
        if (!pEvent->SetEventData(eventData))
        {
            return std::shared_ptr<ScriptEvent>();
        }

        return pEvent;
    }

    void InternalScriptExports::AttachScriptTask(LuaPlus::LuaObject scriptTask)
    {
        LuaPlus::LuaObject temp = scriptTask.Lookup("__object");
        if (!temp.IsNil())
        {
            std::shared_ptr<Task> pTask(static_cast<Task*>(temp.GetLightUserData()));
            g_pApp->GetGameLogic()->AttachTask(pTask);
        }
        else
        {
            LOG_ERROR("Couldn't find __object in script process");
        }
    }

    int InternalScriptExports::CreateActor(const char* pActorArchetype, LuaPlus::LuaObject luaPosition, LuaPlus::LuaObject luaYawPitchRoll)
    {
        // FIXME: Implement this.
        LOG_FATAL("Not implemented yet!");
        //if (!luaPosition.IsTable())
        //{
        //    LOG_ERROR("Invalid object passed to CreateActor(); type = " + std::string(luaPosition.TypeName()));
        //    return Actor::NULL_ACTOR_ID;
        //}

        //if (!luaYawPitchRoll.IsTable())
        //{
        //    LOG_ERROR("Invalid object passed to CreateActor(); type = " + std::string(luaYawPitchRoll.TypeName()));
        //    return Actor::NULL_ACTOR_ID;
        //}

        //math::Vector3f pos(luaPosition["x"].GetFloat(), luaPosition["y"].GetFloat(), luaPosition["z"].GetFloat());
        //math::Vector3f ypr(luaYawPitchRoll["x"].GetFloat(), luaYawPitchRoll["y"].GetFloat(), luaYawPitchRoll["z"].GetFloat());

        //math::Matrix4f initialTransform;
        //initialTransform.BuildYawPitchRoll(ypr.x, ypr.y, ypr.z);
        //initialTransform.SetPosition(pos);

        //TiXmlElement* overloads = nullptr;
        //ActorSharedPointer pActor = g_pApp->m_pGame->vCreateActor(pActorArchetype, overloads, &initialTransform);

        //if (pActor)
        //{
        //    std::shared_ptr<EvtData_New_Actor> pNewActorEvent(LIB_NEW EvtData_New_Actor(pActor->GetActorID()));
        //    IEventManager::Get()->vQueueEvent(pNewActorEvent);
        //    return pActor->GetActorID();
        //}

        return Actor::NULL_ACTOR_ID;
    }

    float InternalScriptExports::WrapPi(float wrapMe)
    {
        // TODO: Implement this.
        LOG_FATAL("Not implemented yet!");
        //return ::WrapPi(wrapMe);
        return uge::PI;
    }

    float InternalScriptExports::GetYRotationFromVector(LuaPlus::LuaObject vec3)
    {
        // TODO: Implement this.
        LOG_FATAL("Not implemented yet!");
        //if (vec3.IsTable())
        //{
        //    math::Vector3f lookAt(vec3["x"].GetFloat(), vec3["y"].GetFloat(), vec3["z"].GetFloat());
        //    return ::GetYRotationFromVector(lookAt);
        //}

        LOG_ERROR("Invalid object passed to GetYRotationFromVector(); type = " + std::string(vec3.TypeName()));
        return 0;
    }



    LuaPlus::LuaObject InternalScriptExports::GetVectorFromRotation(float angleRadians)
    {
        // TODO: Implement this.
        LOG_FATAL("Not implemented yet!");
        return LuaPlus::LuaObject();

        //math::Vector3f result = ::GetVectorFromYRotation(angleRadians);
        //LuaPlus::LuaObject luaResult;
        //luaResult.AssignNewTable(LuaStateManager::Get()->GetLuaState());
        //luaResult.SetNumber("x", result.x);
        //luaResult.SetNumber("y", result.y);
        //luaResult.SetNumber("z", result.z);
        //return luaResult;
    }

    void InternalScriptExports::LuaLog(LuaPlus::LuaObject text)
    {
        if (text.IsConvertibleToString())
        {
            LOG_MSG("Lua", text.ToString());
        }
        else
        {
            LOG_MSG("Lua", "<" + std::string(text.TypeName()) + ">");
        }
    }

    unsigned long InternalScriptExports::GetTickCount()
    {
        // TODO: refactor this to multi-plataform compatibility.
        return ::GetTickCount();
    }


    //---------------------------------------------------------------------------------------------------------------------
    // Script exports for the physics system
    //---------------------------------------------------------------------------------------------------------------------
    void InternalScriptExports::ApplyForce(LuaPlus::LuaObject normalDirLua, float force, int actorId)
    {
        // TODO: Implement this.
        LOG_FATAL("Not implemented yet!");

        //if (normalDirLua.IsTable())
        //{
        //    math::Vector3f normalDir(normalDirLua["x"].GetFloat(), normalDirLua["y"].GetFloat(), normalDirLua["z"].GetFloat());
        //    g_pApp->m_pGame->vGetGamePhysics()->vApplyForce(normalDir, force, actorId);
        //    return;
        //}
        //LOG_ERROR("Invalid object passed to ApplyForce(); type = " + std::string(normalDirLua.TypeName()));
    }

    void InternalScriptExports::ApplyTorque(LuaPlus::LuaObject axisLua, float force, int actorId)
    {
        // TODO: Implement this.
        LOG_FATAL("Not implemented yet!");

        //if (axisLua.IsTable())
        //{
        //    math::Vector3f axis(axisLua["x"].GetFloat(), axisLua["y"].GetFloat(), axisLua["z"].GetFloat());
        //    g_pApp->m_pGame->vGetGamePhysics()->vApplyTorque(axis, force, actorId);
        //    return;
        //}
        //LOG_ERROR("Invalid object passed to ApplyTorque(); type = " + std::string(axisLua.TypeName()));
    }

    //---------------------------------------------------------------------------------------------------------------------
    // This function registers all the ScriptExports functions with the scripting system.  It is called in
    // Application::Init().
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptExports::Register()
    {
        LuaPlus::LuaObject globals = LuaStateManager::Get()->GetGlobalVars();

        // init
        InternalScriptExports::Init();

        // resource loading
        globals.RegisterDirect("LoadAndExecuteScriptResource", &InternalScriptExports::LoadAndExecuteScriptResource);

        // actors
        globals.RegisterDirect("CreateActor", &InternalScriptExports::CreateActor);

        // event system
        globals.RegisterDirect("RegisterEventListener", &InternalScriptExports::RegisterEventListener);
        globals.RegisterDirect("RemoveEventListener", &InternalScriptExports::RemoveEventListener);
        globals.RegisterDirect("QueueEvent", &InternalScriptExports::QueueEvent);
        globals.RegisterDirect("TriggerEvent", &InternalScriptExports::TriggerEvent);

        // process system
        globals.RegisterDirect("AttachTask", &InternalScriptExports::AttachScriptTask);

        // math
        //LuaPlus::LuaObject mathTable = globals.GetByName("GccMath");
        //assert(mathTable.IsTable() && "The table does not exists! Check the pre-init Lua file.");
        //mathTable.RegisterDirect("GetYRotationFromVector", &InternalScriptExports::GetYRotationFromVector);
        //mathTable.RegisterDirect("WrapPi", &InternalScriptExports::WrapPi);
        //mathTable.RegisterDirect("GetVectorFromRotation", &InternalScriptExports::GetVectorFromRotation);

        // misc
        globals.RegisterDirect("Log", &InternalScriptExports::LuaLog);
        globals.RegisterDirect("GetTickCount", &InternalScriptExports::GetTickCount);

        //// Physics
        globals.RegisterDirect("ApplyForce", &InternalScriptExports::ApplyForce);
        globals.RegisterDirect("ApplyTorque", &InternalScriptExports::ApplyTorque);
    }

    //---------------------------------------------------------------------------------------------------------------------
    // This function unregisters all the ScriptExports functions and gives any underlying systems a chance to destroy
    // themselves.  It is called in the Application destructor.
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptExports::Unregister()
    {
        InternalScriptExports::Destroy();
    }

}
