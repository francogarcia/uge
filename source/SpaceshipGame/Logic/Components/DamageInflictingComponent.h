#include <Core/EntityComponent/Component/ActorComponent.h>

namespace sg
{
    namespace Component
    {

        class DamageInflictingComponent;
        typedef std::shared_ptr<DamageInflictingComponent> DamageInflictingComponentSharedPointer;

        /**
         * @class DamageInflictingComponent
         * Component which allows the actor to inflict damage on contact.
         */
        class DamageInflictingComponent : public uge::Component::ActorComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            DamageInflictingComponent();

            /**
             *  Destructor.
             */
            ~DamageInflictingComponent();

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            bool vInit(uge::XMLElement* pInitXMLData) override;

            /**
             *  Initializes the game object after it was instantiated.
             */
            void vPostInit() override;

            /**
             *  Updates the object.
             */
            void vUpdate(const unsigned long dt) override;

            /**
             *  Callback to be used when the object changes its data or state.
             */
            void vOnChange() override;

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            const std::string vGetName() const override;

            int GetDamageOutput() const;
            void SetDamageOutput(const int damageOutput);

        private:
            /// The damage inflicted by an actor which has this component.
            int m_DamageOutput;
        };

    }

}
