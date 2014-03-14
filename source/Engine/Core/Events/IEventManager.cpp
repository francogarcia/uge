#include "GameEngineStd.h"

#include "IEventManager.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    static IEventManager* g_pEventMgr = nullptr;
    GenericObjectFactory<IEventData, EventType> g_eventFactory;

    IEventManager* IEventManager::Get()
    {
        assert(g_pEventMgr && "Invalid event manager!");
        return g_pEventMgr;
    }

    IEventManager::IEventManager(std::string name, bool bIsGlobal)
    {
        if (bIsGlobal)
        {
            if (g_pEventMgr)
            {
                LOG_ERROR("Attempting to create two global event managers! The old one will be destroyed and overwritten with this one.");
                delete g_pEventMgr;
            }

            g_pEventMgr = this;
        }
    }

    IEventManager::~IEventManager()
    {
        if (g_pEventMgr == this)
        {
            g_pEventMgr = nullptr;
        }
    }

}
