#include "GameEngineStd.h"

#include <Debug/Logger.h>

#include <Script/Lua/LuaStateManager.h>
#include <Script/Lua/ScriptTask.h>
#include <Script/Lua/ScriptExports.h>

#include <GameEngineApplication.h>

GameEngineApplication* g_pApp = nullptr;

int main(int argc, char* argv[])
{
    g_pApp = new GameEngineApplication;
    assert(g_pApp && "Could not create the application!");
    if (!g_pApp->vInit())
    {
        std::cerr << "Error creating the application!" << std::endl;

        return -1;
    }

    debug::log::Init("data/debug/LogConfig.xml");

    if (!LuaStateManager::Create())
    {
        std::cerr << "Error creating the state manager!" << std::endl;

        return -1;
    }    

    IScriptManager* pScriptManager = LuaStateManager::Get();

    pScriptManager->vExecuteFile("data/scripts/PreInit.lua");
    ScriptExports::Register();

    pScriptManager->vExecuteString("x = 0");
    pScriptManager->vExecuteString("x = x + 10");
    pScriptManager->vExecuteString("print(x)");
    pScriptManager->vExecuteString("= x");

    // A very simple Lua shell.
    LuaPlus::LuaState* pLuaState = LuaStateManager::Get()->GetLuaState();
    pLuaState->DoFile("data/scripts/Shell.lua"); // ExecuteFile("LuaTask.lua")

    pScriptManager->vExecuteString("print(\"bye!\")");
    pScriptManager->vExecuteString("io.write(x)");

    pLuaState->DoFile("data/LuaTask.lua");

    pScriptManager = nullptr;
    LuaStateManager::Destroy();

    ScriptExports::Unregister();

    debug::log::Destroy();

    return 0;
}
