#include "GameEngineStd.h"

#include "ISceneNodeRenderer.h"

namespace uge
{
    ISceneNodeRenderer::ISceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties)
    {
        assert(pSceneNodeProperties != nullptr && "Invalid scene node!");
    }

    ISceneNodeRenderer::~ISceneNodeRenderer()
    {

    }
}
