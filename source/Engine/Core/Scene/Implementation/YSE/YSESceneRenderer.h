#pragma once

#include <Core/Scene/ISceneRenderer.h>
#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>

#include "YSECamera.h"
#include "YSESceneNodeRenderer.h"

namespace uge
{
    class YSESceneRenderer;
    typedef std::shared_ptr<YSESceneRenderer> YSESceneRendererSharedPointer;

    class ResourceCache;

    class YSESceneRenderer : public IAudioSceneRenderer
    {
    public:
        YSESceneRenderer(IAudioSharedPointer pAudioRenderer, ResourceCache& resourceCache);
        ~YSESceneRenderer();

        virtual void CreateScene(const IScene* const pScene) override;
        virtual const IScene* const GetScene() const override;

        virtual bool vOnUpdate(const unsigned long timeElapsed) override;
        virtual bool vOnRender() override;

        virtual bool vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;
        virtual bool vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;

        virtual void vOnSetCamera(ICameraNodeSharedPointer pCamera) override;
        virtual void vOnUpdateCamera(ICameraNodeSharedPointer pCamera) override;

        virtual IAudioSharedPointer vGetAudioRenderer() override;

        virtual OutputType vGetOutputType() const override
        {
            return OutputType::Aural;
        }

    private:
        // Internal use.
        void RegisterResourceLoaders();

        void AddSceneNodeToScene(SceneNodeSharedPointer pSceneNode);
        YSESceneNodeRenderer CreateSceneNode(const SceneNodeProperties* const pSceneNodeProperties);

    private:
        std::shared_ptr<YSEAudio> m_pAudioRenderer;
        ResourceCache& m_ResourceCache;

        const IScene* m_pScene;
        std::map<ActorID, YSESceneNodeRenderer> m_SceneNodes;

        YSECamera m_Camera;
    };
}
