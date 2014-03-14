#pragma once

namespace uge
{

    class IEventData;

    typedef unsigned int EventType;
    typedef std::shared_ptr<IEventData> IEventDataSharedPointer;

    class IEventData
    {
    public:
        IEventData();

        virtual ~IEventData();

        virtual const EventType& vGetEventType() const = 0;
        virtual unsigned long vGetTimeStamp() const = 0;
        virtual void vSerialize(std::ostrstream& out) const = 0;
        virtual void vDeserialize(std::istrstream& in) = 0;
        virtual IEventDataSharedPointer vCopy() const = 0;
        virtual const char* vGetName() const = 0;
    };

    class BaseEventData : public IEventData
    {
    public:
        explicit BaseEventData(const unsigned long timeStamp = 0u);
        virtual ~BaseEventData();

        virtual const EventType& vGetEventType() const = 0;

        virtual unsigned long vGetTimeStamp() const override;

        virtual void vSerialize(std::ostrstream& out) const override;

        virtual void vDeserialize(std::istrstream& in) override;

        virtual IEventDataSharedPointer vCopy() const = 0;
        virtual const char* vGetName() const = 0;

    private:
        const unsigned long m_TimeStamp;
    };

}
