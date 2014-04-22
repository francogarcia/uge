#include <Core/Events/Event.h>
#include <Core/Events/EventManager.h>

#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptEvent.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Engine/GameApplication/BaseGameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>
#include <Utilities/System/Clock.h>
#include <Utilities/System/Time.h>

#include <stdio.h>

// Receives events from Lua and C++.
class LuaScriptEvent : public uge::lua::ScriptEvent
{
public:
    static const uge::EventType sk_EventType;

    LuaScriptEvent()
        : m_Value(0u)
    {

    }

    explicit LuaScriptEvent(unsigned int value)
        : m_Value(value)
    {

    }

    virtual const uge::EventType& vGetEventType() const override
    {
        return sk_EventType;
    }

    virtual uge::IEventDataSharedPointer vCopy() const override
    {
        std::shared_ptr<LuaScriptEvent> pEvent(LIB_NEW LuaScriptEvent(m_Value));
        pEvent->m_EventData = m_EventData;

        return pEvent;
    }

    virtual void vSerialize(std::ostrstream& out) const override
    {
        out << m_Value;
    }

    virtual void vDeserialize(std::istrstream& in) override
    {
        in >> m_Value;
    }

    virtual const char* vGetName() const override
    {
        return "LuaScriptEvent";
    }

    unsigned int GetValue() const
    {
        return m_Value;
    }

protected:
    virtual void vBuildEventData() override
    {
        m_EventData.AssignNumber(uge::lua::LuaStateManager::Get()->GetLuaState(), m_Value);
    }

    virtual bool vBuildEventFromScript() override
    {
        if (!m_EventData.IsInteger())
        {
            return false;
        }

        m_Value = m_EventData.GetInteger();

        return true;
    }

    EXPORT_FOR_LUA_SCRIPT_EVENT(LuaScriptEvent);

private:
    unsigned int m_Value;
};

const uge::EventType LuaScriptEvent::sk_EventType(0xbd131e2d);

// Receives from Lua.
class ScriptEventFromLua : public uge::lua::ScriptEvent
{
public:
    static const uge::EventType sk_EventType;

    ScriptEventFromLua()
        : m_Value(0u)
    {

    }

    explicit ScriptEventFromLua(unsigned int value)
        : m_Value(value)
    {

    }

    virtual const uge::EventType& vGetEventType() const override
    {
        return sk_EventType;
    }

    virtual uge::IEventDataSharedPointer vCopy() const override
    {
        std::shared_ptr<ScriptEventFromLua> pEvent(LIB_NEW ScriptEventFromLua(m_Value));
        pEvent->m_EventData = m_EventData;

        return pEvent;;
    }

    virtual void vSerialize(std::ostrstream& out) const override
    {
        out << m_Value;
    }

    virtual void vDeserialize(std::istrstream& in) override
    {
        in >> m_Value;
    }

    virtual const char* vGetName() const override
    {
        return "ScriptEventFromLua";
    }

    unsigned int GetValue() const
    {
        return m_Value;
    }

protected:
    virtual bool vBuildEventFromScript() override
    {
        if (!m_EventData.IsInteger())
        {
            return false;
        }

        m_Value = m_EventData.GetInteger();

        return true;
    }

    EXPORT_FOR_LUA_SCRIPT_EVENT(ScriptEventFromLua);

private:
    unsigned int m_Value;
};

const uge::EventType ScriptEventFromLua::sk_EventType(0x864bc680);

// Sends to Lua.
class ScriptEventToLua : public uge::lua::ScriptEvent
{
public:
    static const uge::EventType sk_EventType;

    ScriptEventToLua()
        : m_Value(0u)
    {

    }

    explicit ScriptEventToLua(unsigned int value)
        : m_Value(value)
    {

    }

    virtual const uge::EventType& vGetEventType() const override
    {
        return sk_EventType;
    }

    virtual uge::IEventDataSharedPointer vCopy() const override
    {
        std::shared_ptr<ScriptEventToLua> pEvent(LIB_NEW ScriptEventToLua(m_Value));
        pEvent->m_EventData = m_EventData;

        return pEvent;
    }

    virtual void vSerialize(std::ostrstream& out) const override
    {
        out << m_Value;
    }

    virtual void vDeserialize(std::istrstream& in) override
    {
        in >> m_Value;
    }

    virtual const char* vGetName() const override
    {
        return "ScriptEventToLua";
    }

    unsigned int GetValue() const
    {
        return m_Value;
    }

protected:
    virtual void vBuildEventData() override
    {
        m_EventData.AssignNumber(uge::lua::LuaStateManager::Get()->GetLuaState(), m_Value);
    }

    virtual bool vBuildEventFromScript() override
    {
        if (!m_EventData.IsInteger())
        {
            return false;
        }

        m_Value = m_EventData.GetInteger();

        return true;
    }

    EXPORT_FOR_LUA_SCRIPT_EVENT(ScriptEventToLua);

private:
    unsigned int m_Value;
};

const uge::EventType ScriptEventToLua::sk_EventType(0x42785522);


class EventClass
{
public:
    EventClass()
    {

    }

    ~EventClass()
    {

    }

    void EventHandlerMethod(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<LuaScriptEvent> pData = std::static_pointer_cast<LuaScriptEvent>(pEventData);

        printf("[C++ - EventClass:EventHandlerMethod()]\n");
        printf("     -> Event 'LuaScriptEvent' received! Value = %u\n\n", pData->GetValue());
    }
};

// Receive event from Lua, increment the received value and send new event to Lua.
void EventHandlerFunction(uge::IEventDataSharedPointer pEventData)
{
    std::shared_ptr<ScriptEventFromLua> pData = std::static_pointer_cast<ScriptEventFromLua>(pEventData);

    unsigned int value = pData->GetValue();

    printf("[C++ - EventHandlerFunction()]\n");
    printf("     -> Event 'ScriptEventFromLua' received! Value = %u\n\n", value);

    // Send another event to Lua.
    ++value;
    std::shared_ptr<ScriptEventToLua> pEvent(LIB_NEW ScriptEventToLua(value));
    uge::IEventManager::Get()->vQueueEvent(pEvent);

    // Send event to Lua and C++.
    std::shared_ptr<LuaScriptEvent> pAnotherEvent(LIB_NEW LuaScriptEvent(value));
    uge::IEventManager::Get()->vQueueEvent(pAnotherEvent);
}

class Application : public uge::BaseGameApplication
{
public:
    virtual bool vInit() override
    {
        bool bReturn = uge::BaseGameApplication::vInit();

        return bReturn;
    }

    virtual bool vDestroy() override
    {
        bool bReturn = uge::BaseGameApplication::vDestroy();

        return bReturn;
    }

    virtual bool vRun() override
    {
        REGISTER_LUA_SCRIPT_EVENT(LuaScriptEvent, LuaScriptEvent::sk_EventType);
        REGISTER_LUA_SCRIPT_EVENT(ScriptEventFromLua, ScriptEventFromLua::sk_EventType);
        REGISTER_LUA_SCRIPT_EVENT(ScriptEventToLua, ScriptEventToLua::sk_EventType);

        // C++ event listeners.
        uge::EventListenerDelegate functionDelegate = fastdelegate::FastDelegate1<uge::IEventDataSharedPointer>(EventHandlerFunction);
        uge::IEventManager::Get()->vAddListener(functionDelegate, ScriptEventFromLua::sk_EventType);

        // Lua event listener.
        uge::IScriptManager* pScriptManager = uge::lua::LuaStateManager::Get();
        pScriptManager->vExecuteString("fileName = \"LuaEvent.lua\"");
        pScriptManager->vExecuteString("LoadAndExecuteScriptResource(fileName)");

        // C++ and Lua listener (receive events sent from both languages).
        EventClass eventClass;
        functionDelegate = fastdelegate::MakeDelegate(&eventClass, &EventClass::EventHandlerMethod);
        uge::IEventManager::Get()->vAddListener(functionDelegate, LuaScriptEvent::sk_EventType);

        // Dispatch the initial event to Lua.
        std::shared_ptr<ScriptEventToLua> pEvent(LIB_NEW ScriptEventToLua);
        uge::IEventManager::Get()->vQueueEvent(pEvent);

        // Fake timer to test the events created in Lua.
        unsigned long timeNow = 0u;
        unsigned long lastTime = 0u;
        unsigned long finalTime = 10u;
        while (timeNow < finalTime)
        {
            uge::IEventManager::Get()->vUpdate(uge::IEventManager::kINFINITE);

            m_pGameLogic->vOnUpdate(timeNow, timeNow - lastTime);

            lastTime = timeNow;
            timeNow += 1u;
        }

        return true;
    }

protected:
    virtual uge::BaseGameLogic* vCreateGameLogic() override
    {
        return LIB_NEW uge::BaseGameLogic;
    }

    virtual bool vInitOutputSystems() override
    {
        return true;
    }

    bool vInitResourceCache() override
    {
        const std::string resourceFileName = "data/data.zip";
        int resourceCacheSizeMB = 100; // 100MB
        uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileDevelopmentResource(resourceFileName, "./", uge::ZipFileDevelopmentResource::Mode::Editor);

        return m_Resources.Init(resourceCacheSizeMB, pResourceFile);
    }
};

int main(int argc, char* argv[])
{
    uge::debug::log::Init("LogConfig.xml");

    uge::GameApplication* pGameApplication = LIB_NEW Application;

    if (!pGameApplication->vInit())
    {
        std::cerr << "Error creating the application!" << std::endl;

        return -1;
    }

    if (!pGameApplication->vRun())
    {
        std::cerr << "Error running the application!" << std::endl;

        return -1;
    }

    // Commented as no output system was created.
    //if (!pGameApplication->vDestroy())
    //{
    //    std::cerr << "Error destroying the application!" << std::endl;

    //    return -1;
    //}

    uge::debug::log::Destroy();

    return 0;
}
