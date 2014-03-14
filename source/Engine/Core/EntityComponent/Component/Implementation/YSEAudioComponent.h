#pragma once

#include <Core/EntityComponent/Component/IAuditoryComponent.h>
#include <IO/Output/Audio/Implementation/YSE/YSEAudioBuffer.h>

namespace uge
{

    namespace Component
    {

        class YSEAudioComponent;
        typedef std::shared_ptr<YSEAudioComponent> YSEAudioComponentSharedPointer;
        typedef std::weak_ptr<YSEAudioComponent> YSEAudioComponentWeakPointer;

        class YSEAudioComponent : public IAuditoryComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Construtor.
             */
            YSEAudioComponent();

            /**
             *  Destructor.
             */
            virtual ~YSEAudioComponent();

            /**
             *  Instanciates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData) override;

            /**
             *  Initializes the game object after it was instanciated.
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

            const std::string& GetFileName() const;

            const float GetVolume() const;

            const float GetInitialProgress() const;

            const bool GetLooping() const;

        private:
            std::string m_SceneNodeName;
            std::string m_FileName;

            float m_fVolume;
            float m_fInitialProgress;

            bool m_bLoop;
        };

    }

}
