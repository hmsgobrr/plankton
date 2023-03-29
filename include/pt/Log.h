#ifndef LOG_H
#define LOG_H

#include <memory>

#include "spdlog/spdlog.h"

namespace pt {

/// Class for logging.
class Log {
public:
    static void init();

    static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
    static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
};

}

// Core log macros
#define PT_CORE_TRACE(...)    ::pt::Log::getCoreLogger()->trace(__VA_ARGS__)
#define PT_CORE_INFO(...)     ::pt::Log::getCoreLogger()->info(__VA_ARGS__)
#define PT_CORE_WARN(...)     ::pt::Log::getCoreLogger()->warn(__VA_ARGS__)
#define PT_CORE_ERROR(...)    ::pt::Log::getCoreLogger()->error(__VA_ARGS__)
#define PT_CORE_CRITICAL(...) ::pt::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PT_TRACE(...)    ::pt::Log::getClientLogger()->trace(__VA_ARGS__)
#define PT_INFO(...)     ::pt::Log::getClientLogger()->info(__VA_ARGS__)
#define PT_WARN(...)     ::pt::Log::getClientLogger()->warn(__VA_ARGS__)
#define PT_ERROR(...)    ::pt::Log::getClientLogger()->error(__VA_ARGS__)
#define PT_CRITICAL(...) ::pt::Log::getClientLogger()->critical(__VA_ARGS__)

#endif // LOG_H
