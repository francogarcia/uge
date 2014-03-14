#include <Core/EntityComponent/Entity/ActorFactory.h>

namespace sg
{

    class ActorFactory : public uge::ActorFactory
    {
    public:
        /**
         *  Constructor.
         */
        ActorFactory();

        /**
         *  Destructor.
         */
        ~ActorFactory();

    private:
        void RegisterComponents();
    };

}
