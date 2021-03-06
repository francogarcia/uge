/*
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

#include "ActorComponent.h"

#include <Utilities/Math/MathStd.h>

namespace uge
{

    namespace Component
    {

        class IRenderableComponent;
        typedef std::weak_ptr<IRenderableComponent> IRenderableComponentWeakPointer;
        typedef std::shared_ptr<IRenderableComponent> IRenderableComponentSharedPointer;

        class IRenderableComponent : public ActorComponent
        {
        public:
            /**
             *  Constructor.
             */
            IRenderableComponent() { }

            /**
             *  Destructor.
             */
            virtual ~IRenderableComponent() { }

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData) = 0;

            /**
             *  Initializes the game object after it was instantiated.
             */
            virtual void vPostInit() = 0;

            /**
             *  Updates the object.
             */
            virtual void vUpdate(const unsigned long dt) = 0;

            /**
             *  Callback to be used when the object changes its data or state.
             */
            virtual void vOnChange() = 0;

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            virtual const std::string vGetName() const = 0;

            virtual const std::string& vGetSceneNodeName() const = 0;

        private:
        };

    }

}
