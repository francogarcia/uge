#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptTask.h>
#include <Core/Script/Lua/ScriptExports.h>

#include <Engine/GameLogic/BaseGameLogic.h>

#include <Utilities/Debug/Logger.h>

int main(int argc, char* argv[])
{
    uge::debug::log::Init("data/debug/LogConfig.xml");

    uge::BaseGameLogic gameLogic;

    if (!gameLogic.vInit()) // *g_pApp == game::GameEngineApplication
    {
        std::cerr << "Error creating the application!" << std::endl;

        return -1;
    }

    if (!uge::LuaStateManager::Create())
    {
        std::cerr << "Error creating the state manager!" << std::endl;

        return -1;
    }

    uge::IScriptManager* pScriptManager = uge::LuaStateManager::Get();
    pScriptManager->vExecuteFile("PreInit.lua");
    uge::ScriptExports::Register();
    
    pScriptManager->vExecuteString("x = 1");
    pScriptManager->vExecuteString("x = x + 10");
    pScriptManager->vExecuteString("print(x)");
    pScriptManager->vExecuteString("= x");
    pScriptManager->vExecuteString("fileName = \"LuaTask.lua\"");

    // A very simple Lua shell.
    LuaPlus::LuaState* pLuaState = uge::LuaStateManager::Get()->GetLuaState();
    pLuaState->DoFile("Shell.lua"); // LoadAndExecuteScriptResource(fileName)

    pScriptManager->vExecuteString("print(\"bye!\")");
    pScriptManager->vExecuteString("io.write(x)");

    //pScriptManager->vExecuteString("LoadAndExecuteScriptResource(\"LuaTask.lua\")");
 
    // Fake timer, to test the events created in Lua.
    float fTimeNow = 0.0f;
    float fLastTime = 0.0f;
    float fFinalTime = 1000.0f;
    while (fTimeNow < fFinalTime)
    {
        gameLogic.vOnUpdate(fTimeNow, fTimeNow - fLastTime);

        fLastTime = fTimeNow;
        fTimeNow += 0.01f;
    }

    pScriptManager = nullptr;
    uge::LuaStateManager::Destroy();
    uge::ScriptExports::Unregister();

    uge::debug::log::Destroy();

    return 0;
}
