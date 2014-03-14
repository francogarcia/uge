#pragma once

#include <Core/Scene/IScene.h>
#include <Core/Scene/Scene.h>

namespace uge
{
    class SceneManager
    {
    public:
        SceneManager();

        ~SceneManager();

        bool Init();

        bool Destroy();

        bool Update(const unsigned long timeElapsed);

        bool AddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode);

        ISceneNodeSharedPointer CreateAndAddSceneNode(ActorSharedPointer pActor);

        bool RemoveSceneNode(ActorID actorID);

        ISceneNodeSharedPointer GetSceneNode(ActorID actorID);

        Scene* GetScene() const;

    private:
        // Scene
        Scene* m_pScene;
    };

}
