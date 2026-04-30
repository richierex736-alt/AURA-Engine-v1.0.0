#pragma once

#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace triga {

// ============================================================
// Log Levels
// ============================================================

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Critical
};

// ============================================================
// Logger
// ============================================================

class Logger {
public:
    static Logger& get() {
        static Logger instance;
        return instance;
    }
    
    void init();
    void shutdown();
    
    void setLevel(LogLevel level);
    void setPattern(const std::string& pattern);
    
    void trace(const std::string& msg);
    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
    void critical(const std::string& msg);
    
    // Format logging
    template<typename... Args>
    void log(LogLevel level, fmt::format_string<Args...> fmt, Args&&... args) {
        auto msg = fmt::format(fmt, std::forward<Args>(args)...);
        switch (level) {
            case LogLevel::Trace: trace(msg); break;
            case LogLevel::Debug: debug(msg); break;
            case LogLevel::Info: info(msg); break;
            case LogLevel::Warn: warn(msg); break;
            case LogLevel::Error: error(msg); break;
            case LogLevel::Critical: critical(msg); break;
        }
    }
    
private:
    Logger() = default;
    ~Logger() = default;
    
    std::shared_ptr<spdlog::logger> m_logger;
    LogLevel m_level = LogLevel::Debug;
};

// Shortcut macros
#define TRIGA_TRACE(msg) ::triga::Logger::get().trace(msg)
#define TRIGA_DEBUG(msg) ::triga::Logger::get().debug(msg)
#define TRIGA_INFO(msg) ::triga::Logger::get().info(msg)
#define TRIGA_WARN(msg) ::triga::Logger::get().warn(msg)
#define TRIGA_ERROR(msg) ::triga::Logger::get().error(msg)
#define TRIGA_CRITICAL(msg) ::triga::Logger::get().critical(msg)

} // namespace triga

