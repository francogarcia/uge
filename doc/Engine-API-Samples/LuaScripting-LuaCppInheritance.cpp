#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptTask.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Engine/GameApplication/BaseGameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

class CPP
{
public:
    static const char* const g_sClassName;

    CPP() : m_Value(0)
    {
        LuaPlus::LuaState* pLuaState = uge::lua::LuaStateManager::Get()->GetLuaState();

        m_PrintFunction.AssignNil(pLuaState);
    }

    virtual ~CPP()
    {

    }

    virtual void vPrint()
    {
        if (!m_PrintFunction.IsNil())
        {
            LuaPlus::LuaFunction<void> function(m_PrintFunction);
            function(m_Self);
        }
        else
        {
            printf("C++ class: %d\n", m_Value);
        }
    }

    virtual int vGetValue()
    {
        return m_Value;
    }

    static void RegisterScriptClass()
    {
        LuaPlus::LuaObject metaTable = uge::lua::LuaStateManager::Get()->GetGlobalVars().CreateTable(g_sClassName);
        metaTable.SetObject("__index", metaTable);
        metaTable.SetObject("base", metaTable);
        metaTable.SetBoolean("cpp", true);

        RegisterScriptClassFunctions(metaTable);
        metaTable.RegisterDirect("Create", &CPP::CreateFromScript);
    }

private:
    static void RegisterScriptClassFunctions(LuaPlus::LuaObject& metaTable)
    {
        metaTable.RegisterObjectDirect("vPrint", (CPP*) 0, &CPP::vPrint);
        metaTable.RegisterObjectDirect("vGetValue", (CPP*) 0, &CPP::vGetValue);
    }

    static LuaPlus::LuaObject CreateFromScript(LuaPlus::LuaObject self,
                                               LuaPlus::LuaObject constructionData,
                                               LuaPlus::LuaObject subclass)
    {
        CPP* pObject = LIB_NEW CPP;

        pObject->m_Self.AssignNewTable(uge::lua::LuaStateManager::Get()->GetLuaState());
        if (pObject->BuildCppDataFromScript(subclass, constructionData))
        {
            LuaPlus::LuaObject metaTable = uge::lua::LuaStateManager::Get()->GetGlobalVars().Lookup(g_sClassName);
            LOG_ASSERT(!metaTable.IsNil() && "Invalid meta table!");

            // Saves this object C++ pointer.
            pObject->m_Self.SetLightUserData("__object", pObject);
            pObject->m_Self.SetMetaTable(metaTable);
        }
        else
        {
            pObject->m_Self.AssignNil(uge::lua::LuaStateManager::Get()->GetLuaState());
            SAFE_DELETE(pObject);
        }

        return pObject->m_Self;
    }

    virtual bool BuildCppDataFromScript(LuaPlus::LuaObject scriptClass,
                                        LuaPlus::LuaObject constructionData)
    {
        if (!scriptClass.IsTable())
        {
            LOG_ERROR("Error creating the class from the script.");

            return false;
        }

        // Override the methods of the class.
        LuaPlus::LuaObject luaObject = scriptClass.GetByName("vPrint");
        if (luaObject.IsFunction())
        {
            m_PrintFunction = luaObject;
        }
        // If the method is mandatory, 'else' should return an error. 

        // Override the attributes of the class.
        if (constructionData.IsTable())
        {
            for (LuaPlus::LuaTableIterator constructionDataIterator(constructionData);
                 constructionDataIterator;
                 constructionDataIterator.Next())
            {
                const char* pKey = constructionDataIterator.GetKey().GetString();
                LuaPlus::LuaObject value = constructionDataIterator.GetValue();

                if (uge::StringComp(pKey, "m_Value") && value.IsInteger())
                {
                    m_Value = value.GetInteger();
                }
                else
                {
                    m_Self.SetObject(pKey, value);
                }
            }
        }

        return true;
    }

private:
    LuaPlus::LuaObject m_PrintFunction;
    LuaPlus::LuaObject m_Self;

    int m_Value;
};

const char* const CPP::g_sClassName = "CPP";

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
        CPP cpp;
        cpp.vPrint();

        uge::IScriptManager* pScriptManager = uge::lua::LuaStateManager::Get();
        pScriptManager->vExecuteFile("PreInit.lua");
        CPP::RegisterScriptClass();

        pScriptManager->vExecuteString("fileName = \"LuaClass.lua\"");
        pScriptManager->vExecuteString("LoadAndExecuteScriptResource(fileName)");

        // Fake timer to test the events created in Lua.
        unsigned long timeNow = 0u;
        unsigned long lastTime = 0u;
        unsigned long finalTime = 1000u;
        while (timeNow < finalTime)
        {
            m_pGameLogic->vOnUpdate(timeNow, timeNow - lastTime);

            lastTime = timeNow;
            timeNow += 1u;
        }

        return true;
    }

    virtual uge::BaseGameLogic* vCreateGameLogic() override
    {
        return LIB_NEW uge::BaseGameLogic;
    }

protected:
    virtual bool vInitOutputSystems() override
    {
        return true;
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

    // Commented as the output system was not created.
    //if (!pGameApplication->vDestroy())
    //{
    //    std::cerr << "Error destroying the application!" << std::endl;

    //    return -1;
    //}

    uge::debug::log::Destroy();

    return 0;
}
