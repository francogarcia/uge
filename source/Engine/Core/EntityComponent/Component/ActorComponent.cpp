/**
 * @file ActorComponent.cpp
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "ActorComponent.h"

namespace uge
{

    namespace Component
    {

        ActorComponent::ActorComponent()
        {

        }

        ActorComponent::~ActorComponent()
        {

        }

        const ComponentID ActorComponent::vGetID() const
        {
            return GetComponentID(vGetName());
        }

        void ActorComponent::SetOwner(ActorSharedPointer pOwner)
        {
            assert(pOwner != nullptr && "Invalid owner!");

            m_pActorOwner = pOwner;
        }

        const ActorSharedPointer ActorComponent::GetOwner() const
        {
            return m_pActorOwner;
        }

        const ComponentID GetComponentID(const std::string& componentName)
        {
            ComponentID componentID = std::hash<std::string>()(componentName);

            return componentID;
        }

    }

}
