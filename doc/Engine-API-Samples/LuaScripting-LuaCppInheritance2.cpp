#include <Core/Script/Lua/LuaCppInheritable.h>
#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptTask.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Engine/GameApplication/BaseGameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

class CPP : public uge::lua::CppInheritable
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
        RegisterLuaScriptClass(g_sClassName, CPP::CreateFromScript, CPP::RegisterScriptClassFunctions);
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
        return CreateCppFromLuaScript<CPP>(LIB_NEW CPP,
                                           g_sClassName,
                                           self,
                                           constructionData,
                                           subclass);
    }

    virtual bool vBuildCppDataFromScript(LuaPlus::LuaObject scriptClass,
                                         LuaPlus::LuaObject constructionData) override
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

    if (!pGameApplication->vDestroy())
    {
        std::cerr << "Error destroying the application!" << std::endl;

        return -1;
    }

    uge::debug::log::Destroy();

    return 0;
}
