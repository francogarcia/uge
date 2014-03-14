#pragma once

#include <Utilities/Math/Matrix.h>

namespace uge
{
    enum class OutputType : unsigned char
    {
        Graphical,
        Aural,
        Tactile,
        Haptic
    };

    class IOutput;
    typedef std::shared_ptr<IOutput> IOutputSharedPointer;

    class IOutput
    {
    public:
        IOutput();
        virtual ~IOutput();

        virtual bool vInit() = 0;
        virtual bool vDestroy() = 0;

        virtual OutputType vGetOutputType() const = 0;
    };
}
