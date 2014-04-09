/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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
  */

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
