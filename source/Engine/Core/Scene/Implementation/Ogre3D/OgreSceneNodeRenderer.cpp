#include "GameEngineStd.h"

#include "OgreSceneNodeRenderer.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Utilities/Math/Conversion/OgreMathConversion.h>

#include <Core/Scene/IScene.h>

namespace uge
{
    OgreSceneNodeRenderer::OgreSceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties)
        : ISceneNodeRenderer(pSceneNodeProperties), m_pSceneNodeProperties(pSceneNodeProperties),
          m_pOgreSceneNode(nullptr), m_pEntity(nullptr)
    {

    }

    OgreSceneNodeRenderer::~OgreSceneNodeRenderer()
    {

    }

    bool OgreSceneNodeRenderer::vPreRender()
    {
        if (m_pOgreSceneNode->getParentSceneNode() == nullptr)
        {
            // Root.
            const Matrix4& transform = m_pSceneNodeProperties->GetWorldTransform(); // Global (world).
            m_pOgreSceneNode->setPosition(ToOgreMath(transform.GetPositionVector()));
            m_pOgreSceneNode->setScale(ToOgreMath(transform.GetScaleVector()));
            m_pOgreSceneNode->setOrientation(ToOgreMath(transform.GetRotationQuaternion()));
        }
        else
        {
            // Ogre positions should be local (relative to parent).

            // Using local coordinates (no physics).
            //const Matrix4& transform = m_pSceneNodeProperties->GetToWorld();
            //m_pOgreSceneNode->setPosition(ToOgreMath(transform.GetPositionVector()));
            //m_pOgreSceneNode->setScale(ToOgreMath(transform.GetScaleVector()));
            //m_pOgreSceneNode->setOrientation(ToOgreMath(transform.GetRotationQuaternion()));

            // Convert from global to local.
            const Matrix4& transform =  m_pSceneNodeProperties->GetWorldTransform();
            m_pOgreSceneNode->_setDerivedPosition(ToOgreMath(transform.GetPositionVector()));
            m_pOgreSceneNode->setScale(ToOgreMath(transform.GetScaleVector()));
            m_pOgreSceneNode->_setDerivedOrientation(ToOgreMath(transform.GetRotationQuaternion()));
        }

        return true;
    }

    bool OgreSceneNodeRenderer::vRender()
    {
        // Handled by Ogre3D.
        //Vector3 pos = m_pSceneNodeProperties->GetToWorld().GetPositionVector(); // Local position.

        // TODO: print this to a log.
        //Vector3 pos = ToMath(m_pOgreSceneNode->getPosition()); // World Position
        //printf("[Ogre3D] %s: (%f, %f, %f)\n", m_pSceneNodeProperties->GetName().c_str(), pos.x, pos.y, pos.z);

        return true;
    }

    bool OgreSceneNodeRenderer::vPostRender()
    {
        return true;
    }

    bool OgreSceneNodeRenderer::vIsVisible() const
    {
        // Handled by Ogre3D. Should be handled by the engine.

        return true;
    }

    bool OgreSceneNodeRenderer::vAddChild(ISceneNodeSharedPointer pChildNode)
    {
        //OgreSceneNodeSharedPointer pChildOgreSceneNode = std::dynamic_pointer_cast<OgreSceneNodeRenderer>(pChildNode);

        //// Change the parent of the node.
        //// Dettach it from the original parent.
        //Ogre::SceneNode* pOgreChildNode = pChildOgreSceneNode->m_pOgreSceneNode;
        //pOgreChildNode->getParentSceneNode()->removeChild(pOgreChildNode);

        //// Attach the node to the new parent.
        //m_pOgreSceneNode->addChild(pOgreChildNode);

        return true;
    }

    bool OgreSceneNodeRenderer::vRemoveChild(ActorID actorID)
    {
        //bool bSuccess = false;

        //SceneNodeList::iterator end = m_Children.end();
        //for (SceneNodeList::iterator childSceneNodeIterator = m_Children.begin();
        //     childSceneNodeIterator != end; ++childSceneNodeIterator)
        //{
        //    const SceneNodeProperties* pProperties = (*childSceneNodeIterator)->vGetNodeProperties();
        //    ActorID nodeActorID = pProperties->GetActorID();
        //    if (nodeActorID != Actor::NULL_ACTOR_ID && actorID == nodeActorID)
        //    {
        //        OgreSceneNodeSharedPointer pChildOgreSceneNode = std::dynamic_pointer_cast<OgreSceneNodeRenderer>(*childSceneNodeIterator);
        //        Ogre::SceneNode* pOgreChildNode = pChildOgreSceneNode->m_pOgreSceneNode;

        //        m_pOgreSceneNode->removeChild(pOgreChildNode);

        //        bSuccess = true;

        //        break;
        //    }
        //}

        return true;
    }
}
