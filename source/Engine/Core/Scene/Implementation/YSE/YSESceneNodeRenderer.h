#pragma once

#include <Core/EntityComponent/Component/Implementation/YSEAudioComponent.h>
#include <Core/Scene/ISceneNodeRenderer.h>
#include <Core/Scene/SceneNode.h>

#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>

namespace uge
{

    class YSESceneNodeRenderer;
    typedef std::shared_ptr<YSESceneNodeRenderer> YSESceneNodeSharedPointer;

    class YSESceneRenderer;

    class YSESceneNodeRenderer : public ISceneNodeRenderer
    {
        friend class YSESceneRenderer;

    public:
        YSESceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties, IAudioBuffer* pAudioBuffer);
        virtual ~YSESceneNodeRenderer();

        virtual bool vPreRender() override;
        virtual bool vRender() override;
        virtual bool vPostRender() override;

        virtual bool vIsVisible() const override;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) override;
        virtual bool vRemoveChild(ActorID actorID) override;

    protected:
        const SceneNodeProperties* const m_pSceneNodeProperties;

        IAudioBuffer* m_pAudioBuffer;
    };

}
