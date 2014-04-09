/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#pragma once

// Extracted from: http://www.ogre3d.org/forums/viewtopic.php?f=2&t=67620

#include "DynamicLineDrawer.h"

namespace uge
{

    /** Implements the bullet debug draw interface for drawing with ogre.
        \ingroup Misc
    */
    class CDebugDraw :
        public btIDebugDraw
    {
    public:
        CDebugDraw(Ogre::SceneManager* Scene, btDynamicsWorld* World);
        ~CDebugDraw();

        /** Moves the data from the world to the ogre object.
            Should be called once every frame.
        */
        void		Update();

    protected:
        void setDebugMode(int DebugMode);
        int getDebugMode() const;

        // these implement the debug/drawing interface, no need to call them from the outside
        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
        void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
                              btScalar distance, int lifeTime, const btVector3& color);
        void reportErrorWarning(const char* warningString);
        void draw3dText(const btVector3& location, const char* textString);
        void drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
        void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2,
                          const btVector3& color, btScalar alpha);


    private:
        std::vector<Ogre::Vector2> UnitCircle;

        CDynamicLineDrawer* DebugLineDrawer;
        Ogre::SceneNode*	DebugDrawerNode;
        btDynamicsWorld*	World;
        bool				IsActive;
    };

}
