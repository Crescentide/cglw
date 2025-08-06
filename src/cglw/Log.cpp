//
// Created by kirut on 8/6/2025.
//

#include "Log.h"

namespace cglw {
    void Log::glLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
        // 131169	"Frame-buffer sRGB capability mismatch."
        // 131185	"Buffer detailed info: Buffer object usage hint is GL_STATIC_DRAW."
        // 131218	"Program/shader state performance warning: Fragment shader is not optimized."
        // 131204	"Texture state usage warning: Texture being used without defined sampling."
        //        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        //            return;

        auto srcToStr = [](GLenum src) {
            switch (src) {
                case GL_DEBUG_SOURCE_API: return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
                case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
                case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
                case GL_DEBUG_SOURCE_APPLICATION: return "Application";
                case GL_DEBUG_SOURCE_OTHER: return "Other";
                default: return "Unknown";
            }
        };

        auto typeToStr = [](GLenum t) {
            switch (t) {
                case GL_DEBUG_TYPE_ERROR: return "Error";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";
                case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
                case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
                case GL_DEBUG_TYPE_MARKER: return "Marker";
                case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
                case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
                case GL_DEBUG_TYPE_OTHER: return "Other";
                default: return "Unknown";
            }
        };

        auto getSeverity = [](GLenum sev) {
            switch (sev) {
                case GL_DEBUG_SEVERITY_HIGH: return "High";
                case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
                case GL_DEBUG_SEVERITY_LOW: return "Low";
                case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
                default: return "Unknown";
            }
        };

        static constexpr std::string_view LOG_TAG = "OpenGL";
        std::string fullLogMsg = std::format("ID: {}, Source: {}, Type: {}, Severity: {}\n"
                                      "\t{}",
                                      id, srcToStr(source), typeToStr(type), getSeverity(severity), message);

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH: {
                Log::critical(LOG_TAG, fullLogMsg);
            } break;
            case GL_DEBUG_SEVERITY_MEDIUM: {
                Log::error(LOG_TAG, fullLogMsg);
            } break;
            case GL_DEBUG_SEVERITY_LOW: {
                Log::warn(LOG_TAG, fullLogMsg);
            } break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: {
                Log::info(LOG_TAG, fullLogMsg);
            } break;
            default:
                return; // don't expect anything else
        }
    }
    std::string_view Log::typeToString(LogType pType) {
        switch (pType) {
            case LogType::Info: return "Info";
            case LogType::Debug: return "Debug";
            case LogType::Warn: return "Warn";
            case LogType::Trace: return "Trace";
            case LogType::Error: return "Error";
            case LogType::Critical: return "Critical";
            default: return "Unknown";
        }
    }
    void Log::setCallback(const std::function<void(LogType, std::string_view, std::string)>&pCallback) {
        callback = pCallback;
    }
    void Log::enable(const std::function<void(LogType, std::string_view, std::string)> &pCallback) {
        callback = pCallback;

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(glLog, nullptr);
    }
}// namespace CGL