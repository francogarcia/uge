#pragma once

namespace uge
{

    /**
     *  Converts a ASCII string to a Unicode string.
     * @param text : a ASCII string.
     * @return : a Unicode string.
     */
    std::wstring StringToWString(const std::string& text);

    /**
     *  Converts a Unicode string to a ASCII string.
     * @param text : a Unicode string.
     * @return : a ASCII string.
     */
    std::string WStringToString(const std::wstring& wtext);

    /**
     *  Converts the characters of a string to lower case.
     * @param text : input string.
     * @return : a copy of the input string will all characterers in lower case.
     */
    std::string StringToLower(const std::string& text);

    /**
     *  Converts the characters of a unicode string to lower case.
     * @param text : input string.
     * @return : a copy of the input string will all characterers in lower case.
     */
    std::wstring WStringToLower(const std::wstring& wtext);

    /**
     *  Converts the characters of a string to upper case.
     * @param text : input string.
     * @return : a copy of the input string will all characterers in upper case.
     */
    std::string StringToUpper(const std::string& text);

    /**
     *  Converts the characters of a unicode string to lower case.
     * @param text : input string.
     * @return : a copy of the input string will all characterers in upper case.
     */
    std::wstring WStringToUpper(const std::wstring& wtext);

    /**
     *  Compares two strings in a case insensitive way.
     * @param str1 : first string.
     * @param str2 : second string.
     * @return : true if the strings are equal, false otherwise.
     */
    bool StringCompCaseInsensitive(std::string str1, std::string str2);

    /**
     *  Compares two Unicode strings in a case insensitive way.
     * @param str1 : first string.
     * @param str2 : second string.
     * @return : true if the strings are equal, false otherwise.
     */
    bool WStringCompCaseInsensitive(std::wstring wstr1, std::wstring wstr2);

    /**
     *  Converts a string to an integer.
     * @param text : the input value as a string.
     * @return : the string converted to int.
     */
    int StringToInt(const std::string& text);

    /**
     *  Converts a wstring to an integer.
     * @param wtext : the input value as a wstring.
     * @return : the wstring converted to int.
     */
    int WStringToInt(const std::wstring& wtext);

    /**
     *  Converts a string to float.
     * @param text : the input value as a string.
     * @return : the float representation of the string.
     */
    float StringToFloat(const std::string& text);

    /**
     *  Converts a wstring to float.
     * @param wtext : the input value as a wstring.
     * @return : the float representation of the wstring.
     */
    float WStringToFloat(const std::wstring& wtext);

    /**
     *  Converts an integer to a string.
     * @param number : an integer number.
     * @return : a string representing the number.
     */
    std::string IntToString(const int& number);

    /**
     *  Converts an integer to a wstring.
     * @param number : an integer number.
     * @return : a wstring representing the number.
     */
    std::wstring IntToWString(const int& number);

    /**
     *  Converts a float number to a string.
     * @param number : an float number.
     * @return : a string representing the number.
     */
    std::string FloatToString(const float& number);

    /**
     *  Converts a float number to a wstring.
     * @param number : an float number.
     * @return : a wstring representing the number.
     */
    std::wstring FloatToWString(const float& number);

    // FIXME: remove this after adding regex to preload.
    // TODO: create another for wstrings.
    bool WildcardMatch(const char* pPattern, const char* pString);

    void SplitString(const std::string& str, std::vector<std::string> strVec, char delimiter);

    void SplitWString(const std::string& wStr, std::vector<std::string> wStrVec, char wDelimiter);

    bool StringBeginsWith(const std::string& str, const std::string& startingStr);

    bool WStringBeginsWith(const std::wstring& wStr, const std::wstring& wStartingStr);

    bool StringEndsWith(const std::string& str, const std::string& endingStr);

    bool WStringEndsWith(const std::wstring& wStr, const std::wstring& wEndingStr);

    std::string StringReplaceAll(const std::string& str, const std::string& findWhatPattern, const std::string& replaceWith);

    std::wstring WStringReplaceAll(const std::wstring& wstr, const std::wstring& findWhatPattern, const std::wstring& replaceWith);

}
