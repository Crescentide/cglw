//
// Created by kirut on 8/6/2025.
//

#ifndef CGL_LOG_H
#define CGL_LOG_H

#include "glad/gl.h"
#include <format>
#include <functional>
#include <string_view>

namespace cglw {
    enum class LogType {
        Info,
        Debug,
        Warn,
        Trace,
        Error,
        Critical
    };

    struct LogFlags {
        unsigned int enableInfo: 1 = true;      // Denotes useful information
        unsigned int enableDebug: 1 = true;     // Denotes testing and when stuff is successful
        unsigned int enableWarn: 1 = true;      // Denotes user errors or invalid states
        unsigned int enableTrace: 1 = true;     // Denotes when things are created
        unsigned int enableError: 1 = true;     // Denotes when things fail but recoverable
        unsigned int enableCritical: 1 = true;  // Denotes when things fail but NOT recoverable
        unsigned int enableOpenGL: 1 = true;    // logging that OpenGL itself does
        unsigned int padding: 1 = false;
    };

    class Log {
        static inline std::function<void(LogType, std::string_view, std::string)> callback; // logs are enabled by providing callback
        static inline LogFlags flags;

        template<typename... Args>
        static void logBase(LogType type, std::string_view origin, std::format_string<Args...> fmt, Args&&... args);

        static void glLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                          const GLchar *message, const void *userParam);
    public:
        using Type = LogType;
        using Flags = LogFlags;

        static void enable(const std::function<void(LogType type, std::string_view origin, std::string msg)>& pCallback,
                           const LogFlags& pEnabledLogs);

        static constexpr std::string_view typeToStr(LogType type) {
            switch (type) {
                case LogType::Info: return "Info";
                case LogType::Debug: return "Debug";
                case LogType::Warn: return "Warn";
                case LogType::Trace: return "Trace";
                case LogType::Error: return "Error";
                case LogType::Critical: return "Critical";
            }
            return "Unknown";
        }
        static constexpr bool isEnabled(LogType type) {
            switch (type) {
                case LogType::Info: return flags.enableInfo;
                case LogType::Debug: return flags.enableDebug;
                case LogType::Warn: return flags.enableWarn;
                case LogType::Trace: return flags.enableTrace;
                case LogType::Error: return flags.enableError;
                case LogType::Critical: return flags.enableCritical;
            }
            return false;
        }

        //region Normal Logs
        static void info(std::string_view origin, std::string_view message) {
            logBase(LogType::Info, origin, "{}", message);
        }

        static void debug(std::string_view origin, std::string_view message) {
            logBase(LogType::Debug, origin, "{}", message);
        }

        static void warn(std::string_view origin, std::string_view message) {
            logBase(LogType::Warn, origin, "{}", message);
        }

        static void trace(std::string_view origin, std::string_view message) {
            logBase(LogType::Trace, origin, "{}", message);
        }

        static void error(std::string_view origin, std::string_view message) {
            logBase(LogType::Error, origin, "{}", message);
        }

        static void critical(std::string_view origin, std::string_view message) {
            logBase(LogType::Critical, origin, "{}", message);
        }
        //endregion

        //region Formatting Logs
        template <typename... Args>
        static void info(std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
            logBase(LogType::Info, origin, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void debug(std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
            logBase(LogType::Debug, origin, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void warn(std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
            logBase(LogType::Warn, origin, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void trace(std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
            logBase(LogType::Trace, origin, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void error(std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
            logBase(LogType::Error, origin, fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void critical(std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
            logBase(LogType::Critical, origin, fmt, std::forward<Args>(args)...);
        }
        //endregion
    };

    template<typename... Args>
    void Log::logBase(Type type, std::string_view origin, std::format_string<Args...> fmt, Args&&... args) {
        if (!callback || !isEnabled(type)) return; // callback not assigned;

        std::string msg = std::format(fmt, std::forward<Args>(args)...);

        callback(type, origin, msg);
    }
}// namespace CGL

#endif//CGL_LOG_H
