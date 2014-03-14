#include "GameEngineStd.h"

#include "Event.h"

namespace uge
{

    IEventData::IEventData()
    {

    }

    IEventData::~IEventData()
    {

    }

    BaseEventData::BaseEventData(const unsigned long timeStamp) : m_TimeStamp(timeStamp)
    {

    }

    BaseEventData::~BaseEventData()
    {

    }

    unsigned long BaseEventData::vGetTimeStamp() const
    {
        return m_TimeStamp;
    }

    void BaseEventData::vSerialize(std::ostrstream& out) const
    {

    }

    void BaseEventData::vDeserialize(std::istrstream& in)
    {

    }

}
