#include "GameEngineStd.h"

#include "Logger.h"

#include <Utilities/String/StringUtil.h>
#include <Utilities/System/Time.h>

namespace uge
{
    namespace debug
    {
        namespace log
        {
#ifdef _DEBUG
            static const char* ERRORLOG_FILENAME = "data/debug/log_d.log";

            const unsigned char ERRORFLAG_DEFAULT =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
            const unsigned char ERRORFLAG_FATAL =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
            const unsigned char WARNINGFLAG_DEFAULT =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
            const unsigned char LOGFLAG_DEFAULT =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
#elif NDEBUG
            static const char* ERRORLOG_FILENAME = "data/debug/log.log";

            const unsigned char ERRORFLAG_DEFAULT =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
            const unsigned char ERRORFLAG_FATAL =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
            const unsigned char WARNINGFLAG_DEFAULT =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
            const unsigned char LOGFLAG_DEFAULT =	(LOGFLAG_WRITE_TO_DEBUGGER | LOGFLAG_WRITE_TO_LOG_FILE);
#else
            static const char* ERRORLOG_FILENAME = "data/debug/log.log";

            const unsigned char ERRORFLAG_DEFAULT =		0;
            const unsigned char ERRORFLAG_FATAL =       0;
            const unsigned char WARNINGFLAG_DEFAULT =	0;
            const unsigned char LOGFLAG_DEFAULT =		0;
#endif

            class LogMessenger
            {
            public:
                enum class ErrorDialogResult : unsigned char
                {
                    LOG_ERROR_ABORT,
                    LOG_ERROR_RETRY,
                    LOG_ERROR_IGNORE
                };

                typedef std::map<std::string, unsigned char> Tags;
                typedef std::list<debug::log::ErrorMessenger*> ErrorMessengerList;

                LogMessenger();
                ~LogMessenger();

                void Init(const std::string& configFileName);

                void Log(const std::string& tag,
                         const std::string& message,
                         const char* const functionName,
                         const char* const sourceFile,
                         unsigned int sourceFileLineNumber);

                void SetDisplayFlags(const std::string& tag, unsigned int flags);

                void AddErrorMessenger(debug::log::ErrorMessenger* pErrorMessenger);
                debug::log::LogMessenger::ErrorDialogResult Error(const std::string& errorMessage,
                        bool bIsFatal,
                        const char* const functionName,
                        const char* const sourceFile,
                        unsigned int sourceFileLineNumber);

            private:
                void OutputBufferToLogs(const std::string& buffer, unsigned char flags);
                void WriteLogToFile(const std::string& logData);
                void GetOutputBuffer(std::string& outOutputBuffer,
                                     const std::string& tag,
                                     const std::string& message,
                                     const char* const functionName,
                                     const char* const sourceFile,
                                     unsigned int sourceFileLineNumber);

                Tags m_Tags;
                ErrorMessengerList m_ErrorMessengers;

                std::mutex m_TagsMutex;
                std::mutex m_ErrorMessengersMutex;
            };

            static LogMessenger* gs_pLogMessenger = nullptr;

            LogMessenger::LogMessenger()
            {
                SetDisplayFlags("ERROR", ERRORFLAG_DEFAULT);
                SetDisplayFlags("FATAL", ERRORFLAG_FATAL);
                SetDisplayFlags("WARNING", WARNINGFLAG_DEFAULT);
                SetDisplayFlags("INFO", LOGFLAG_DEFAULT);
            }

            LogMessenger::~LogMessenger()
            {
                m_ErrorMessengersMutex.lock();

                for (auto messengerIt = m_ErrorMessengers.begin();
                     messengerIt != m_ErrorMessengers.end();
                     ++messengerIt)
                {
                    debug::log::ErrorMessenger* pMessenger = *messengerIt;
                    delete pMessenger;
                    pMessenger = nullptr;
                }
                m_ErrorMessengers.clear();

                m_ErrorMessengersMutex.unlock();
            }

            void LogMessenger::Init(const std::string& configFileName)
            {
                uge::XMLFile logConfigFile;
                if (logConfigFile.OpenFile(configFileName, File::FileMode::FileReadWrite))
                {
                    uge::XMLElement xmlRootElement(logConfigFile.GetRootElement());
                    if (!xmlRootElement.IsGood())
                    {
                        return;
                    }

                    for (uge::XMLElement xmlElement = xmlRootElement.GetFirstChildElement();
                         xmlElement.IsGood();
                         xmlElement = xmlElement.GetNextSiblingElement())
                    {
                        unsigned char flags = 0;
                        std::string tag("");
                        xmlElement.GetAttribute("tag", &tag);

                        int debugger = 0;
                        xmlElement.GetIntAttribute("debugger", &debugger);
                        if (debugger)
                        {
                            flags |= LOGFLAG_WRITE_TO_DEBUGGER;
                        }

                        int logfile = 0;
                        xmlElement.GetIntAttribute("file", &logfile);
                        if (logfile)
                        {
                            flags |= LOGFLAG_WRITE_TO_LOG_FILE;
                        }

                        SetDisplayFlags(tag, flags);
                    }
                }
            }

            void LogMessenger::Log(const std::string& tag,
                                   const std::string& message,
                                   const char* const functionName,
                                   const char* const sourceFile,
                                   unsigned int sourceFileLineNumber)
            {
                m_TagsMutex.lock();

                Tags::iterator tagsIt = m_Tags.find(tag);
                if (tagsIt != m_Tags.end())
                {
                    m_TagsMutex.unlock();

                    std::string buffer;
                    GetOutputBuffer(buffer, tag, message, functionName, sourceFile, sourceFileLineNumber);
                    OutputBufferToLogs(buffer, tagsIt->second);
                }
                else
                {
                    m_TagsMutex.unlock();
                }
            }

            void LogMessenger::SetDisplayFlags(const std::string& tag, unsigned int flags)
            {
                m_TagsMutex.lock();

                if (flags != 0)
                {
                    Tags::iterator tagsIt = m_Tags.find(tag);
                    if (tagsIt == m_Tags.end())
                    {
                        m_Tags.insert(std::make_pair(tag, flags));
                    }
                    else
                    {
                        tagsIt->second = flags;
                    }
                }
                else
                {
                    m_Tags.erase(tag);
                }

                m_TagsMutex.unlock();
            }

            void LogMessenger::AddErrorMessenger(debug::log::ErrorMessenger* pErrorMessenger)
            {
                m_ErrorMessengersMutex.lock();

                m_ErrorMessengers.push_back(pErrorMessenger);

                m_ErrorMessengersMutex.unlock();
            }

            debug::log::LogMessenger::ErrorDialogResult
            LogMessenger::Error(const std::string& errorMessage,
                                bool bIsFatal,
                                const char* const functionName,
                                const char* const sourceFile,
                                unsigned int sourceFileLineNumber)
            {
                std::string tag = ((bIsFatal) ? ("FATAL") : ("ERROR"));

                std::string buffer;
                GetOutputBuffer(buffer, tag, errorMessage, functionName, sourceFile, sourceFileLineNumber);

                m_TagsMutex.lock();

                Tags::iterator tagIt = m_Tags.find(tag);
                if (tagIt != m_Tags.end())
                {
                    OutputBufferToLogs(buffer, tagIt->second);
                }

                m_TagsMutex.unlock();

                // TODO: remove this later.
                //#if _DEBUG
                // TODO: add support for other platforms.
#if _WIN32
                int result = ::MessageBoxA(nullptr, buffer.c_str(), tag.c_str(), MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_DEFBUTTON3);

                switch (result)
                {
                    case IDIGNORE:
                        return debug::log::LogMessenger::ErrorDialogResult::LOG_ERROR_IGNORE;

                    case IDABORT:
                        __debugbreak();
                        return debug::log::LogMessenger::ErrorDialogResult::LOG_ERROR_RETRY;

                    case IDRETRY:
                        return debug::log::LogMessenger::ErrorDialogResult::LOG_ERROR_RETRY;

                    default:
                        return debug::log::LogMessenger::ErrorDialogResult::LOG_ERROR_RETRY;
                }
#endif // #if _WIN32
                //#endif // #if _DEBUG
            }

            void LogMessenger::OutputBufferToLogs(const std::string& buffer, unsigned char flags)
            {
                if ((flags & LOGFLAG_WRITE_TO_LOG_FILE) > 0)
                {
                    WriteLogToFile(buffer);
                }
#if _DEBUG
#if _WIN32
                if ((flags & LOGFLAG_WRITE_TO_DEBUGGER) > 0)
                {
                    ::OutputDebugStringA(buffer.c_str());
                }
#endif
#endif
            }

            void LogMessenger::WriteLogToFile(const std::string& logData)
            {
                TextFile logFile;
                if (logFile.OpenFile(ERRORLOG_FILENAME, File::FileMode::FileWriteAppend))
                {
                    logFile.Write(logData);
                    logFile.CloseFile();
                }
            }

            void LogMessenger::GetOutputBuffer(std::string& outOutputBuffer,
                                               const std::string& tag,
                                               const std::string& message,
                                               const char* const functionName,
                                               const char* const sourceFile,
                                               unsigned int sourceFileLineNumber)
            {
                if (!tag.empty())
                {
                    outOutputBuffer = "[" + tag + "] " + message;
                }
                else
                {
                    outOutputBuffer = message;
                }

                if (functionName != nullptr)
                {
                    outOutputBuffer += "\nFunction: ";
                    outOutputBuffer += functionName;
                }

                if (sourceFile != nullptr)
                {
                    outOutputBuffer += "\nFile: ";
                    outOutputBuffer += sourceFile;
                }

                if (sourceFileLineNumber != 0)
                {
                    outOutputBuffer += "\nLine: ";
                    outOutputBuffer += IntToString(sourceFileLineNumber);
                }

                outOutputBuffer += "\nDate/Time: ";
                outOutputBuffer += Time::GetDateAndTimeAsString();

                outOutputBuffer += "\n\n";
            }

            void Init(std::string configFileName)
            {
                if (!gs_pLogMessenger)
                {
                    gs_pLogMessenger = LIB_NEW debug::log::LogMessenger;
                    gs_pLogMessenger->Init(configFileName);
                }
            }

            void Destroy()
            {
                delete gs_pLogMessenger;
                gs_pLogMessenger = nullptr;
            }

            void Log(const std::string& tag,
                     const std::string& errorMessage,
                     const char* const functionName,
                     const char* const sourceFile,
                     unsigned int sourceFileLineNumber)
            {
                assert(gs_pLogMessenger && "Logger was not initialized!");

                gs_pLogMessenger->Log(tag,
                                      errorMessage,
                                      functionName,
                                      sourceFile,
                                      sourceFileLineNumber);
            }

            void SetDisplayFlags(const std::string& tag, unsigned char flags)
            {
                assert(gs_pLogMessenger && "Logger was not initialized!");

                gs_pLogMessenger->SetDisplayFlags(tag, flags);
            }

            ErrorMessenger::ErrorMessenger() : m_bIsEnabled(true)
            {
                gs_pLogMessenger->AddErrorMessenger(this);
            }

            void ErrorMessenger::Show(const std::string& errorMessage,
                                      bool bIsFatal,
                                      const char* const functionName,
                                      const char* const sourceFile,
                                      unsigned int sourceFileLineNumber)
            {
                if (m_bIsEnabled)
                {
                    if (gs_pLogMessenger->Error(errorMessage,
                                                bIsFatal,
                                                functionName,
                                                sourceFile,
                                                sourceFileLineNumber) == LogMessenger::ErrorDialogResult::LOG_ERROR_IGNORE)
                    {
                        m_bIsEnabled = false;
                    }
                }
            }
        }
    }

}
