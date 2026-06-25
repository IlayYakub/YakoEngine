#include "Core/Log/Log.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace
{

spdlog::level::level_enum ConvertToSpdlogLevelEnum(const ::YakoEngine::LogSeverity& severity)
{
    switch (severity)
    {
        case ::YakoEngine::LogSeverity::Trace:
            return spdlog::level::trace;
        case ::YakoEngine::LogSeverity::Debug:
            return spdlog::level::debug;
        case ::YakoEngine::LogSeverity::Info:
            return spdlog::level::info;
        case ::YakoEngine::LogSeverity::Warn:
            return spdlog::level::warn;
        case ::YakoEngine::LogSeverity::Error:
            return spdlog::level::err;
        case ::YakoEngine::LogSeverity::Fatal:
            return spdlog::level::critical;
        default:
            std::unreachable();
    }
}

}  // namespace

namespace YakoEngine
{

class Log::Impl
{
public:
    Impl()
        : m_engineLogger(nullptr)
        , m_userLogger(nullptr)
    {
        // Engine logger
        auto rotation_file_sink =
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>("engine_log.txt", 1048576 * 5, 5);
        auto engine_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto dup_filter_sink     = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(3));
        auto engine_dist_sink    = std::make_shared<spdlog::sinks::dist_sink_mt>();

        dup_filter_sink->add_sink(engine_console_sink);
        engine_dist_sink->add_sink(rotation_file_sink);
        engine_dist_sink->add_sink(dup_filter_sink);

        m_engineLogger = std::make_shared<spdlog::logger>("engineLogger", engine_dist_sink);
        m_engineLogger->set_pattern(
            "\033[2;90m[%Y-%m-%d %H:%M:%S]\033[0m  %^[%l]%$ "
            "\033[94m[%s:%# -> %!]\033[0m [Engine] %v"
        );
        m_engineLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(m_engineLogger);

        // User logger
        auto user_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        m_userLogger           = std::make_shared<spdlog::logger>("userLogger", user_console_sink);
        m_userLogger->set_pattern(
            "\033[2;90m[%Y-%m-%d %H:%M:%S]\033[0m  %^[%l]%$ "
            "\033[94m[%s:%# -> %!]\033[0m [User] %v"
        );
        m_userLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(m_userLogger);
    }

    void log(
        const Logger&      logger,
        const LogSeverity& severity,
        const std::string& category,
        const std::string& formatted_str,
        const char*        file,
        int                line,
        const char*        func
    ) const
    {
        std::shared_ptr<spdlog::logger> current_logger = (logger == Logger::Engine) ? m_engineLogger : m_userLogger;
        spdlog::level::level_enum       spdlog_level   = ConvertToSpdlogLevelEnum(severity);

        std::string final_msg = std::format("[{}] {}", category, formatted_str);

        spdlog::source_loc loc{file, line, func};
        current_logger->log(loc, spdlog_level, final_msg);
    }

private:
    std::shared_ptr<spdlog::logger> m_engineLogger{nullptr};
    std::shared_ptr<spdlog::logger> m_userLogger{nullptr};
};

Log::Log()
    : m_pImpl(std::make_unique<Impl>())
{
}

Log::~Log()
{
}

void Log::WriteLog(
    const Logger&      logger,
    const LogSeverity& severity,
    const std::string& category,
    const std::string& formatted_str,
    const char*        file,
    int                line,
    const char*        func
)
{
    m_pImpl->log(logger, severity, category, formatted_str, file, line, func);
}

}  // namespace YakoEngine