/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#pragma once

#include <Core/EntityComponent/Component/IGraphicalComponent.h>
#include <Utilities/Math/MathStd.h>

namespace uge
{

    namespace Component
    {
    
        class OgreGraphicalComponent;
        typedef std::shared_ptr<OgreGraphicalComponent> OgreGraphicalComponentSharedPointer;
        typedef std::weak_ptr<OgreGraphicalComponent> OgreGraphicalComponentWeakPointer;

        class OgreGraphicalComponent : public IGraphicalComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            OgreGraphicalComponent();

            /**
             *  Destructor.
             */
            ~OgreGraphicalComponent();

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData) override;

            /**
             *  Initializes the game object after it was instantiated.
             */
            virtual void vPostInit() override;

            /**
             *  Updates the object.
             */
            virtual void vUpdate(const unsigned long dt) override;

            /**
             *  Callback to be used when the object changes its data or state.
             */
            virtual void vOnChange() override;

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            virtual const std::string vGetName() const override;

            virtual const std::string& vGetSceneNodeName() const override;

            const std::string& GetMeshFileName() const;

            const std::string& GetMaterialFileName() const;

            Ogre::SceneNode* GetSceneNode() const;

            void SetSceneNode(Ogre::SceneNode* pSceneNode);

        private:
            std::string m_NodeName;
            std::string m_MeshFileName;
            std::string m_MaterialFileName;
            Ogre::SceneNode* m_pSceneNode;
        };

    }

}
