#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptTask.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Engine/GameApplication/BaseGameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

#include <Utilities/Debug/Logger.h>

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

        //uge::LuaStateManager::Destroy();
        //uge::ScriptExports::Unregister();

        return bReturn;
    }

    virtual bool vRun() override
    {
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

    virtual bool vInitLuaScripting() override
    {
        if (!uge::lua::LuaStateManager::Create())
        {
            std::cerr << "Error creating the state manager!" << std::endl;

            return false;
        }

        uge::IScriptManager* pScriptManager = uge::lua::LuaStateManager::Get();
        pScriptManager->vExecuteFile("PreInit.lua");
        uge::lua::ScriptExports::Register();
        uge::lua::ScriptTask::RegisterScriptClass();

        pScriptManager->vExecuteString("x = 1");
        pScriptManager->vExecuteString("x = x + 10");
        pScriptManager->vExecuteString("print(x)");
        pScriptManager->vExecuteString("= x");
        pScriptManager->vExecuteString("fileName = \"LuaTask.lua\"");
        pScriptManager->vExecuteString("LoadAndExecuteScriptResource(fileName)");

        // A very simple Lua shell.
        pScriptManager->vExecuteFile("Shell.lua");
        //pScriptManager->vExecuteString("LoadAndExecuteScriptResource(\"LuaTask.lua\")");

        pScriptManager->vExecuteString("print(\"bye!\")");
        pScriptManager->vExecuteString("io.write(x)");


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

    uge::debug::log::Destroy();

    return 0;
}
