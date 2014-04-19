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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once
//========================================================================
// BaseScriptComponent.h - Component for exposing actors to Lua
//
// Part of the GameCode4 Application
//
// GameCode4 is the sample application that encapsulates much of the source code
// discussed in "Game Coding Complete - 4th Edition" by Mike McShaffry and David
// "Rez" Graham, published by Charles River Media.
// ISBN-10: 1133776574 | ISBN-13: 978-1133776574
//
// If this source code has found it's way to you, and you think it has helped you
// in any way, do the authors a favor and buy a new copy of the book - there are
// detailed explanations in it that compliment this code well. Buy a copy at Amazon.com
// by clicking here:
//    http://www.amazon.com/gp/product/1133776574/ref=olp_product_details?ie=UTF8&me=&seller=
//
// There's a companion web site at http://www.mcshaffry.com/GameCode/
//
// The source code is managed and maintained through Google Code:
//    http://code.google.com/p/gamecode4/
//
// (c) Copyright 2012 Michael L. McShaffry and David Graham
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser GPL v3
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
// http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
//
// You should have received a copy of the GNU Lesser GPL v3
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//========================================================================

#include <Core/EntityComponent/Component/ScriptComponentInterface.h>

namespace uge
{

    namespace Component
    {

        //---------------------------------------------------------------------------------------------------------------------
        // BaseScriptComponent class
        // Chapter 12, page 337
        //---------------------------------------------------------------------------------------------------------------------
        class BaseLuaScriptComponent : public ScriptComponentInterface
        {
        public:
            static const char* g_ComponentName;

            BaseLuaScriptComponent();
            virtual ~BaseLuaScriptComponent();

            /**
             *  Instanciates the game object, loading the default data provided for it.
             * @param pInitXMLData : pointer to a XML element containing the object's load data.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(uge::XMLElement* pInitXMLData) override;

            /**
             *  Initializes the game object after it was instanciated.
             */
            virtual void vPostInit() override;

            /**
             *  Updates the object.
             * This method must be implemented by the subclass.
             * @param dt : time elapsed since the last update.
             */
            virtual void vUpdate(const unsigned long dt) = 0;

            /**
             *  Callback to be used when the object changes its data or state.
             * This method must be implemented by the subclass.
             */
            virtual void vOnChange() = 0;

            /**
             *  Gets the name of the component.
             * @return : the name of the component, as defined by the subclass.
             */
            virtual const std::string vGetName() const override;

            static void RegisterScriptFunctions();
            static void UnregisterScriptFunctions();

        private:
            void CreateScriptObject();

            // component script functions
            // FIXME
            //LuaPlus::LuaObject GetActorID();

            //// physics component script functions
            //LuaPlus::LuaObject GetPos();
            //void SetPos(LuaPlus::LuaObject newPos);
            //LuaPlus::LuaObject GetLookAt() const;
            //float GetYOrientationRadians() const;
            //void RotateY(float angleRadians);
            //void SetPosition(float x, float y, float z);
            //void LookAt(Vec3 target);
            //void Stop();

            std::string m_scriptObjectName;
            std::string m_constructorName;
            std::string m_destructorName;

            LuaPlus::LuaObject m_scriptObject;
            LuaPlus::LuaObject m_scriptConstructor;
            LuaPlus::LuaObject m_scriptDestructor;
        };

    }

}
