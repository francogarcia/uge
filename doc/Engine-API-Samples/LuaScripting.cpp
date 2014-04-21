#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptTask.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Utilities/Debug/Logger.h>

int main(int argc, char* argv[])
{
    uge::debug::log::Init("LogConfig.xml");

    if (!uge::lua::LuaStateManager::Create())
    {
        std::cerr << "Error creating the state manager!" << std::endl;

        return -1;
    }

    uge::IScriptManager* pScriptManager = uge::lua::LuaStateManager::Get();
    pScriptManager->vExecuteFile("PreInit.lua");
    uge::lua::ScriptExports::Register();
    uge::lua::ScriptTask::RegisterScriptClass();
    
    pScriptManager->vExecuteString("x = 1");
    pScriptManager->vExecuteString("x = x + 10");
    pScriptManager->vExecuteString("print(x)");
    pScriptManager->vExecuteString("= x");

    // A very simple Lua shell.
    pScriptManager->vExecuteFile("Shell.lua");

    pScriptManager->vExecuteString("print(\"bye!\")");
    pScriptManager->vExecuteString("io.write(x)");

    pScriptManager = nullptr;
    uge::lua::LuaStateManager::Destroy();
    uge::lua::ScriptExports::Unregister();

    uge::debug::log::Destroy();

    return 0;
}
