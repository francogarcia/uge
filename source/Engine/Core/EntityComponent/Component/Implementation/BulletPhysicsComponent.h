/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include <Core/EntityComponent/Component/IPhysicsComponent.h>

#include <Core/Physics/IPhysics.h>
#include <Utilities/Math/MathStd.h>

namespace uge
{

    namespace Component
    {

        class BulletPhysicsComponent;
        typedef std::shared_ptr<BulletPhysicsComponent> BulletPhysicsComponentSharedPointer;

        class BulletPhysicsComponent : public IPhysicsComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            BulletPhysicsComponent();

            /**
             *  Destructor.
             */
            virtual ~BulletPhysicsComponent();

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData);

            /**
             *  Initializes the game object after it was instantiated.
             */
            virtual void vPostInit();

            /**
             *  Updates the object.
             */
            virtual void vUpdate(const unsigned long dt);

            /**
             *  Callback to be used when the object changes its data or state.
             */
            virtual void vOnChange();

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            virtual const std::string vGetName() const;

            virtual void vApplyForce(const Vector3& direction, const float fNewtons);
            virtual void vApplyTorque(const Vector3& direction, const float fNewtons);
            virtual bool vKinematicMove(const Matrix4& transform);

            virtual void vApplyAcceleration(float fAcceleration);
            virtual void vRemoveAcceleration();
            virtual void vApplyAngularAcceleration(float fAcceleration);
            virtual void vRemoveAngularAcceleration();

            virtual float vGetMaxVelocity() const;
            virtual const Vector3 vGetVelocity() const;
            virtual void vSetVelocity(const Vector3& velocity);

            virtual void vRotateY(float fAngle);
            virtual void vSetPosition(const Vector3& position);
            virtual void vStop();

            void SetPhysicsSystem(IPhysics* pPhysics);

            virtual void vCreateShape();

        protected:
            virtual void vBuildRigidBodyTransform();

        protected:
            /*
              TODO: add more attributes to the component:

              <BulletPhysicsComponent>
                <LinearDamping x="0.0f" y="0.0f" z="0.0f"/>
                <AngularDamping x="0.0f" y="0.0f" z="0.0f"/>
                <InitialVelocity x="0.0f" y="0.0f" z="0.0f">
                <MaxVelocity v="0.0f"/>
                <MaxAngularVelocity v="0.0f"/>
                <MaxAcceleration a="0.0f"/>
              </BulletPhysicsComponent>

             */

            float m_fAcceleration;
            float m_fAngularAcceleration;
            //float m_fMaxAcceleration;

            //Vector3 m_fInitialVelocity;
            float m_fMaxVelocity;
            float m_fMaxAngularVelocity;

            Vector3 m_LinearFactor;
            Vector3 m_AngularFactor;

            Vector3 m_RigidBodyLocalPosition;
            Vector3 m_RigidBodyLocalOrientation;
            Vector3 m_RigidBodyLocalScale;

            IPhysics* m_pPhysics;
        };

    }

}
