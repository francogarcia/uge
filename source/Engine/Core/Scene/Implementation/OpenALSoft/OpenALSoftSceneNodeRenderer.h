#pragma once

#include <Core/EntityComponent/Component/Implementation/OpenALSoftAudioComponent.h>
#include <Core/Scene/ISceneNodeRenderer.h>
#include <Core/Scene/SceneNode.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>

namespace uge
{

    class OpenALSoftSceneNodeRenderer;
    typedef std::shared_ptr<OpenALSoftSceneNodeRenderer> OpenALSoftSceneNodeSharedPointer;

    class OpenALSoftSceneRenderer;

    class OpenALSoftSceneNodeRenderer : public ISceneNodeRenderer
    {
        friend class OpenALSoftSceneRenderer;

    public:
        OpenALSoftSceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties, IAudioBuffer* pAudioBuffer);
        virtual ~OpenALSoftSceneNodeRenderer();

        virtual bool vPreRender() override;
        virtual bool vRender() override;
        virtual bool vPostRender() override;

        virtual bool vIsVisible() const override;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) override;
        virtual bool vRemoveChild(ActorID actorID) override;

    protected:
        const SceneNodeProperties* const m_pSceneNodeProperties;

        //Component::OpenALSoftGraphicalComponentWeakPointer m_pRenderComponent;
        IAudioBuffer* m_pAudioBuffer;
    };

}
