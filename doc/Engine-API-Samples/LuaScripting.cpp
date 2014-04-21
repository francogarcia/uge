#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptTask.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Utilities/Debug/Logger.h>

int main(int argc, char* argv[])
{
    uge::debug::log::Init("LogConfig.xml");

    if (!uge::LuaStateManager::Create())
    {
        std::cerr << "Error creating the state manager!" << std::endl;

        return -1;
    }

    uge::IScriptManager* pScriptManager = uge::LuaStateManager::Get();
    pScriptManager->vExecuteFile("PreInit.lua");
    uge::ScriptExports::Register();
    uge::ScriptTask::RegisterScriptClass();
    
    pScriptManager->vExecuteString("x = 1");
    pScriptManager->vExecuteString("x = x + 10");
    pScriptManager->vExecuteString("print(x)");
    pScriptManager->vExecuteString("= x");
    pScriptManager->vExecuteString("fileName = \"LuaTask.lua\"");

    // A very simple Lua shell.
    LuaPlus::LuaState* pLuaState = uge::LuaStateManager::Get()->GetLuaState();
    pLuaState->DoFile("Shell.lua");

    pScriptManager->vExecuteString("print(\"bye!\")");
    pScriptManager->vExecuteString("io.write(x)");

    pScriptManager = nullptr;
    uge::LuaStateManager::Destroy();
    uge::ScriptExports::Unregister();

    uge::debug::log::Destroy();

    return 0;
}
