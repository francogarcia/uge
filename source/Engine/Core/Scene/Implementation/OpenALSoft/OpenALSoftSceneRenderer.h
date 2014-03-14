#pragma once

#include <Core/Scene/ISceneRenderer.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>

#include "OpenALSoftCamera.h"
#include "OpenALSoftSceneNodeRenderer.h"

namespace uge
{
    class OpenALSoftSceneRenderer;
    typedef std::shared_ptr<OpenALSoftSceneRenderer> OpenALSoftSceneRendererSharedPointer;

    class ResourceCache;

    class OpenALSoftSceneRenderer : public IAudioSceneRenderer
    {
    public:
        OpenALSoftSceneRenderer(IAudioSharedPointer pAudioRenderer, ResourceCache& resourceCache);
        ~OpenALSoftSceneRenderer();

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
        OpenALSoftSceneNodeRenderer CreateSceneNode(const SceneNodeProperties* const pSceneNodeProperties);

    private:
        std::shared_ptr<OpenALSoftAudio> m_pAudioRenderer;
        ResourceCache& m_ResourceCache;

        const IScene* m_pScene;
        std::map<ActorID, OpenALSoftSceneNodeRenderer> m_SceneNodes;

        OpenALSoftCamera m_Camera;
    };
}
