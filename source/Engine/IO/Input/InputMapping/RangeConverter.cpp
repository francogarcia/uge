//
// Input Mapping Demo
// By Mike Lewis, June 2011
// http://scribblings-by-apoch.googlecode.com/
//
// Wrapper class for converting raw input range values to sensitivity-calibrated range values
//

#include "GameEngineStd.h"

#include "RangeConverter.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    namespace InputMapping
    {


        //
        // Construct the converter and load the conversion table provided
        //
        RangeConverter::RangeConverter()
        {

        }

        void RangeConverter::AddConverter(Range rangeID, XMLElement& rangeElement)
        {
            Converter converter;
            XMLElement inputRangeElement(rangeElement.GetFirstChildElement("InputRange"));
            assert(inputRangeElement.IsGood());
            inputRangeElement.GetFloatAttribute("minimum_value", &converter.fMinimumInputValue);
            inputRangeElement.GetFloatAttribute("maximum_value", &converter.fMaximumInputValue);

            XMLElement outputRangeElement(rangeElement.GetFirstChildElement("OutputRange"));
            assert(outputRangeElement.IsGood());
            outputRangeElement.GetFloatAttribute("minimum_value", &converter.fMinimumOutputValue);
            outputRangeElement.GetFloatAttribute("maximum_value", &converter.fMaximumOutputValue);

            if ((converter.fMaximumInputValue < converter.fMinimumInputValue) || (converter.fMaximumOutputValue < converter.fMinimumOutputValue))
            {
                LOG_FATAL("Invalid input range conversion");
            }

            m_ConversionMap.insert(std::make_pair(rangeID, converter));
        }

    }

}
