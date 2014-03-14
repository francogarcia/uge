/**
 * @file Task.h
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include <Utilities/File/File.h>
#include <Utilities/File/XMLFile.h>

namespace uge
{
    namespace debug
    {
        namespace log
        {
            const unsigned char LOGFLAG_WRITE_TO_LOG_FILE =		1 << 0;
            const unsigned char LOGFLAG_WRITE_TO_DEBUGGER =		1 << 1;

            void Init(std::string configFileName);
            void Destroy();

            void Log(const std::string& tag,
                     const std::string& errorMessage,
                     const char* const functionName,
                     const char* const sourceFile,
                     unsigned int sourceFileLineNumber);

            void SetDisplayFlags(const std::string& tag, unsigned char flags);

            class ErrorMessenger
            {
            public:
                ErrorMessenger();

                void Show(const std::string& errorMessage,
                          bool bIsFatal,
                          const char* const functionName,
                          const char* const sourceFile,
                          unsigned int sourceFileLineNumber);

            private:
                bool m_bIsEnabled;
            };
        }
    }
}

#define LOG_FATAL(str) \
    do \
    { \
        static ::uge::debug::log::ErrorMessenger* pErrorMessenger = LIB_NEW ::uge::debug::log::ErrorMessenger; \
        std::string s((str)); \
        pErrorMessenger->Show(s, true, __FUNCTION__, __FILE__, __LINE__); \
    } \
    while (0)\
         
#if 1 // TODO / FIXME: swap building the final release version.
//#ifndef NDEBUG

#define LOG_ERROR(str) \
    do \
    { \
        static ::uge::debug::log::ErrorMessenger* pErrorMessenger = LIB_NEW ::uge::debug::log::ErrorMessenger; \
        std::string s((str)); \
        pErrorMessenger->Show(s, false, __FUNCTION__, __FILE__, __LINE__); \
    } \
    while (0) \
         
#define LOG_WARNING(str) \
    do \
    { \
        std::string s((str)); \
        ::uge::debug::log::Log("WARNING", s, __FUNCTION__, __FILE__, __LINE__); \
    }\
    while (0) \
         
#define LOG_INFO(str) \
    do \
    { \
        std::string s((str)); \
        ::uge::debug::log::Log("INFO", s, nullptr, nullptr, 0); \
    } \
    while (0) \
         
#define LOG_MSG(tag, message) \
    do \
    { \
        std::string s((message)); \
        ::uge::debug::log::Log(tag, s, nullptr, nullptr, 0); \
    } \
    while (0) \
         
#define LOG_ASSERT(expr) \
    do \
    { \
        if (!(expr)) \
        { \
            static ::uge::debug::log::ErrorMessenger* pErrorMessenger = LIB_NEW ::uge::debug::log::ErrorMessenger; \
            pErrorMessenger->Show(#expr, false, __FUNCTION__, __FILE__, __LINE__); \
        } \
    } \
    while (0) \
         
#else

#define LOG_ERROR(str) do { (void)sizeof(str); } while(0)
#define LOG_WARNING(str) do { (void)sizeof(str); } while(0)
#define LOG_INFO(str) do { (void)sizeof(str); } while(0)
#define LOG_MSG(tag, message) do { (void)sizeof(tag); (void)sizeof(message); } while(0)
#define LOG_ASSERT(expr) do { (void)sizeof(expr); } while(0)

#endif  // !defined NDEBUG
