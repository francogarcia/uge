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

#include "GameEngineStd.h"

#include "StringUtil.h"

#pragma once

namespace uge
{

    std::wstring StringToWString(const std::string& text)
    {
        // C++11
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

        return std::wstring(converter.from_bytes(text));
    }

    std::string WStringToString(const std::wstring& wtext)
    {
        // C++11
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

        return std::string(converter.to_bytes(wtext));
    }

    std::string StringToLower(const std::string& text)
    {
        std::string buffer(text);
        std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

        return buffer;
    }

    std::wstring WStringToLower(const std::wstring& wtext)
    {
        std::wstring buffer(wtext);
        std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

        return buffer;
    }

    std::string StringToUpper(const std::string& text)
    {
        std::string buffer(text);
        std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);

        return buffer;
    }

    std::wstring WStringToUpper(const std::wstring& wtext)
    {
        std::wstring buffer(wtext);
        std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);

        return buffer;
    }

    bool StringCompCaseInsensitive(std::string str1, std::string str2)
    {
        return (StringToLower(str1) == StringToLower(str2));
    }

    bool WStringCompCaseInsensitive(std::wstring wstr1, std::wstring wstr2)
    {
        return (WStringToLower(wstr1) == WStringToLower(wstr2));
    }

    int StringToInt(const std::string& text)
    {
        std::istringstream str(text);
        int number;

        str >> std::dec >> number;

        return number;
    }

    int WStringToInt(const std::wstring& wtext)
    {
        std::wistringstream wstr(wtext);
        int number;

        wstr >> std::dec >> number;

        return number;
    }

    unsigned int StringToUInt(const std::string& text)
    {
        std::istringstream str(text);
        unsigned int number;

        str >> std::dec >> number;

        return number;
    }

    unsigned int WStringToUInt(const std::wstring& wtext)
    {
        std::wistringstream wstr(wtext);
        unsigned int number;

        wstr >> std::dec >> number;

        return number;
    }

    float StringToFloat(const std::string& text)
    {
        std::istringstream str(text);
        float number;

        str >> std::dec >> number;

        return number;
    }

    float WStringToFloat(const std::wstring& wtext)
    {
        std::wistringstream wstr(wtext);
        float number;

        wstr >> std::dec >> number;

        return number;
    }

    std::string IntToString(const int& number)
    {
        //std::stringstream str;
        //str << number;

        //return str.str();

        return std::to_string(number);
    }

    std::wstring IntToWString(const int& number)
    {
        //std::wstringstream wstr;
        //wstr << number;

        //return wstr.str();

        return std::to_wstring(number);
    }

    std::string UIntToString(const unsigned int& number)
    {
        //std::stringstream str;
        //str << number;

        //return str.str();

        return std::to_string(number);
    }

    std::wstring UIntToWString(const unsigned int& number)
    {
        //std::wstringstream wstr;
        //wstr << number;

        //return wstr.str();

        return std::to_wstring(number);
    }

    std::string FloatToString(const float& number)
    {
        //std::stringstream str;
        //str << number;

        //return str.str();

        return std::to_string(number);
    }

    std::wstring FloatToWString(const float& number)
    {
        //std::wstringstream wstr;
        //wstr << number;

        //return wstr.str();

        return std::to_wstring(number);
    }

    bool WildcardMatch(const char* pPattern, const char* pString)
    {
        int i, star;

    new_segment:

        star = 0;
        if (*pPattern == '*')
        {
            star = 1;
            do
            {
                pPattern++;
            }
            while (*pPattern == '*');   /* enddo */
        } /* endif */

    test_match:

        for (i = 0; pPattern[i] && (pPattern[i] != '*'); i++)
        {
            //if (mapCaseTable[str[i]] != mapCaseTable[pat[i]]) {
            if (pString[i] != pPattern[i])
            {
                if (!pString[i])
                {
                    return false;
                }
                if ((pPattern[i] == '?') && (pString[i] != '.'))
                {
                    continue;
                }
                if (!star)
                {
                    return false;
                }
                pString++;
                goto test_match;
            }
        }
        if (pPattern[i] == '*')
        {
            pString += i;
            pPattern += i;
            goto new_segment;
        }
        if (!pString[i])
        {
            return true;
        }
        if (i && pPattern[i - 1] == '*')
        {
            return true;
        }
        if (!star)
        {
            return false;
        }
        pString++;
        goto test_match;
    }

    void SplitString(const std::string& str, std::vector<std::string> strVec, char delimiter)
    {
        strVec.clear();
        size_t strLen = str.size();
        if (strLen == 0)
        {
            return;
        }

        size_t startIndex = 0;
        size_t indexOfDel = str.find_first_of(delimiter, startIndex);
        while (indexOfDel != std::string::npos)
        {
            strVec.push_back(str.substr(startIndex, indexOfDel - startIndex));

            startIndex = indexOfDel + 1;
            if (startIndex >= strLen)
            {
                break;
            }
            indexOfDel = str.find_first_of(delimiter, startIndex);
        }

        if (startIndex < strLen)
        {
            strVec.push_back(str.substr(startIndex));
        }
    }

    void SplitWString(const std::string& wStr, std::vector<std::string> wStrVec, char wDelimiter)
    {
        wStrVec.clear();
        size_t strLen = wStr.size();
        if (strLen == 0)
        {
            return;
        }

        size_t startIndex = 0;
        size_t indexOfDel = wStr.find_first_of(wDelimiter, startIndex);
        while (indexOfDel != std::string::npos)
        {
            wStrVec.push_back(wStr.substr(startIndex, indexOfDel - startIndex));

            startIndex = indexOfDel + 1;
            if (startIndex >= strLen)
            {
                break;
            }
            indexOfDel = wStr.find_first_of(wDelimiter, startIndex);
        }

        if (startIndex < strLen)
        {
            wStrVec.push_back(wStr.substr(startIndex));
        }
    }

    bool StringBeginsWith(const std::string& str, const std::string& startingStr)
    {
        const size_t stringSize = str.length();
        const size_t endingSize = startingStr.length();
        if (stringSize < endingSize)
        {
            return false;
        }

        return (str.compare(0, endingSize, startingStr) == 0);
    }

    bool WStringBeginsWith(const std::wstring& wStr, const std::wstring& startingStr)
    {
        const size_t stringSize = wStr.length();
        const size_t endingSize = startingStr.length();
        if (stringSize < endingSize)
        {
            return false;
        }

        return (wStr.compare(0, endingSize, startingStr) == 0);
    }

    bool StringEndsWith(const std::string& str, const std::string& endingStr)
    {
        const size_t stringSize = str.length();
        const size_t endingSize = endingStr.length();
        if (stringSize < endingSize)
        {
            return false;
        }

        return (str.compare(stringSize - endingSize, endingSize, endingStr) == 0);
    }

    bool WStringEndsWith(const std::wstring& wStr, const std::wstring& wEndingStr)
    {
        const size_t stringSize = wStr.length();
        const size_t endingSize = wEndingStr.length();
        if (stringSize < endingSize)
        {
            return false;
        }

        return (wStr.compare(stringSize - endingSize, endingSize, wEndingStr) == 0);
    }

    std::string StringReplaceAll(const std::string& str, const std::string& findWhatPattern, const std::string& replaceWith)
    {
        // C++11
        std::regex matches(findWhatPattern);

        return std::regex_replace(str, matches, replaceWith);
    }

    std::wstring WStringReplaceAll(const std::wstring& wstr, const std::wstring& findWhatPattern, const std::wstring& replaceWith)
    {
        // C++11
        std::wregex matches(findWhatPattern);

        return std::regex_replace(wstr, matches, replaceWith);
    }

}
