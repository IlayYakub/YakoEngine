#pragma once

#include "Utility/Singleton.h"

#include <string>
#include <memory>

namespace YakoEngine
{

enum class LogSeverity
{
    None,
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

enum class Logger
{
    Engine,
    User
};

class Log final : public Singleton<Log>
{
    friend class Singleton<Log>;

public:
    void WriteLog(
        const Logger&      logger,
        const LogSeverity& severity,
        const std::string& category,
        const std::string& formatted_str,
        const char*        file,
        int                line,
        const char*        func
    );

private:
    explicit Log();
    virtual ~Log();

    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}  // namespace YakoEngine

#define YAKO_LOG(logger_type, severity, category_name, message, ...)                        \
    do                                                                                      \
    {                                                                                       \
        if (auto log_instance = ::YakoEngine::Log::GetInstance(); log_instance.has_value()) \
        {                                                                                   \
            log_instance.value()->WriteLog(                                                 \
                ::YakoEngine::Logger::logger_type,                                          \
                ::YakoEngine::LogSeverity::severity,                                        \
                #category_name,                                                             \
                std::format(message __VA_OPT__(, ) __VA_ARGS__),                            \
                __FILE__,                                                                   \
                __LINE__,                                                                   \
                __FUNCTION__                                                                \
            );                                                                              \
        }                                                                                   \
    } while (0)

#define YAKO_DEBUG_BREAK() __debugbreak()

// Engine macros
#define YAKO_TRACE(category, message, ...) YAKO_LOG(Engine, Trace, category, message __VA_OPT__(, ) __VA_ARGS__)
#define YAKO_DEBUG(category, message, ...) YAKO_LOG(Engine, Debug, category, message __VA_OPT__(, ) __VA_ARGS__)
#define YAKO_INFO(category, message, ...) YAKO_LOG(Engine, Info, category, message __VA_OPT__(, ) __VA_ARGS__)
#define YAKO_WARN(category, message, ...) YAKO_LOG(Engine, Warn, category, message __VA_OPT__(, ) __VA_ARGS__)
#define YAKO_ERROR(category, message, ...) YAKO_LOG(Engine, Error, category, message __VA_OPT__(, ) __VA_ARGS__)
#define YAKO_FATAL(category, message, ...)                                     \
    do                                                                         \
    {                                                                          \
        YAKO_LOG(Engine, Fatal, category, message __VA_OPT__(, ) __VA_ARGS__); \
        YAKO_DEBUG_BREAK();                                                    \
    } while (0)

// User macros
#define USER_TRACE(category, message, ...) YAKO_LOG(User, Trace, category, message __VA_OPT__(, ) __VA_ARGS__)
#define USER_DEBUG(category, message, ...) YAKO_LOG(User, Debug, category, message __VA_OPT__(, ) __VA_ARGS__)
#define USER_INFO(category, message, ...) YAKO_LOG(User, Info, category, message __VA_OPT__(, ) __VA_ARGS__)
#define USER_WARN(category, message, ...) YAKO_LOG(User, Warn, category, message __VA_OPT__(, ) __VA_ARGS__)
#define USER_ERROR(category, message, ...) YAKO_LOG(User, Error, category, message __VA_OPT__(, ) __VA_ARGS__)
#define USER_FATAL(category, message, ...)                                   \
    do                                                                       \
    {                                                                        \
        YAKO_LOG(User, Fatal, category, message __VA_OPT__(, ) __VA_ARGS__); \
        YAKO_DEBUG_BREAK();                                                  \
    } while (0)