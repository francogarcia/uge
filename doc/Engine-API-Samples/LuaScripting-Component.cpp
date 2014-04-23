#include <Core/EntityComponent/Component/Implementation/LuaScriptComponent.h>
#include <Core/EntityComponent/Entity/Actor.h>

#include <Core/Script/Lua/LuaStateManager.h>

#include <Engine/GameApplication/BaseGameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

#include <Utilities/Debug/Logger.h>

#include <stdio.h>

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
        uge::ActorSharedPointer pActor = m_pGameLogic->vCreateActor("actor.xml");

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
