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

#include <Core/EntityComponent/Component/ScriptComponentInterface.h>

namespace uge
{

    namespace Component
    {

        class LuaScriptComponent : public ScriptComponentInterface
        {
        public:
            static const char* g_ComponentName;

            LuaScriptComponent();
            virtual ~LuaScriptComponent();

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
            virtual void vUpdate(const unsigned long dt);

            /**
             *  Callback to be used when the object changes its data or state.
             * This method must be implemented by the subclass.
             */
            virtual void vOnChange();

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

            std::string m_ScriptResourceFileName;

            std::string m_ScriptObjectName;
            std::string m_ConstructorName;
            std::string m_DestructorName;

            LuaPlus::LuaObject m_ScriptObject;
            LuaPlus::LuaObject m_ScriptConstructor;
            LuaPlus::LuaObject m_ScriptDestructor;
        };

    }

}
