/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
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

#pragma once

// Dependencies
#include "InputTypes.h"

#include <Utilities/File/XMLFile.h>

namespace uge
{

    namespace InputMapping
    {

        class RangeConverter
        {
            // Construction
        public:
            RangeConverter();
            void AddConverter(Range rangeID, XMLElement& rangeElement);

            // Conversion interface
            template <typename RangeType>
            RangeType Convert(Range rangeid, RangeType invalue) const
            {
                const auto& iter = m_ConversionMap.find(rangeid);
                if (iter == m_ConversionMap.end())
                {
                    return invalue;
                }

                return iter->second.Convert<RangeType>(invalue);
            }

            // Internal helpers
        private:
            struct Converter
            {
                float fMinimumInputValue;
                float fMaximumInputValue;

                float fMinimumOutputValue;
                float fMaximumOutputValue;

                template <typename RangeType>
                RangeType Convert(RangeType invalue) const
                {
                    float fValue = static_cast<float>(invalue);
                    if (fValue < fMinimumInputValue)
                    {
                        fValue = fMinimumInputValue;
                    }
                    else if (fValue > fMaximumInputValue)
                    {
                        fValue = fMaximumInputValue;
                    }

                    float interpolationfactor = (fValue - fMinimumInputValue) / (fMaximumInputValue - fMinimumInputValue);
                    return static_cast<RangeType>((interpolationfactor * (fMaximumOutputValue - fMinimumOutputValue)) + fMinimumOutputValue);
                }
            };

            std::map<Range, Converter> m_ConversionMap;
        };

    }

}
