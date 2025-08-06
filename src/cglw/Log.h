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

    class Log { // TODO: add ability to choose which log types you want
        static inline std::function<void(LogType, std::string_view, std::string)> callback; // logs are enabled by providing callback
//        static inline uint32_t enabledTypes = 0x00000000;



        template<typename... Args>
        static void logBase(LogType type, std::string_view origin, std::format_string<Args...> fmt, Args&&... args);

        static void glLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                          const GLchar *message, const void *userParam);
    public:
        using Type = LogType;
        bool allowDebug = false;
        bool allowGLLogs = false;

        Log() = delete;
        static void enable(const std::function<void(LogType type, std::string_view origin, std::string msg)>& pCallback);

        static std::string_view typeToString(LogType pType);
        static void setCallback(const std::function<void(LogType type, std::string_view origin, std::string msg)>&pCallback);

//region Normal
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

//region Formatting
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
        if (!callback) return; // callback not assigned

        std::string msg = std::format(fmt, std::forward<Args>(args)...);

        callback(type, origin, msg);
    }



}// namespace CGL

#endif//CGL_LOG_H
