#pragma once

#include <android/log.h>
#include <format>
#include <string_view>

namespace Log
{
    constexpr std::string_view Tag = "KotlinTestApp";

    namespace Internal {
        template<typename... Args>
        void Print(android_LogPriority priority, std::format_string<Args...> fmt, Args&&... args) {
            std::string msg = std::format(fmt, std::forward<Args>(args)...);

            __android_log_print(priority, Tag.data(), "%s", msg.c_str());
        }
    }

    template<typename... Args>
    void Verbose(std::format_string<Args...> fmt, Args&&... args) {
        Internal::Print(ANDROID_LOG_VERBOSE, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Debug(std::format_string<Args...> fmt, Args&&... args) {
        Internal::Print(ANDROID_LOG_DEBUG, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Info(std::format_string<Args...> fmt, Args&&... args) {
        Internal::Print(ANDROID_LOG_INFO, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Warn(std::format_string<Args...> fmt, Args&&... args) {
        Internal::Print(ANDROID_LOG_WARN, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Error(std::format_string<Args...> fmt, Args&&... args) {
        Internal::Print(ANDROID_LOG_ERROR, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Fatal(std::format_string<Args...> fmt, Args&&... args) {
        Internal::Print(ANDROID_LOG_FATAL, fmt, std::forward<Args>(args)...);
    }
}
