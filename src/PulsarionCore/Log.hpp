#pragma once

#include "Core.hpp"

#include <memory>
#include <spdlog/spdlog.h>

namespace Pulsarion
{
    class PULSARION_API Log
    {
    public:
        static void Init();
        [[nodiscard]] static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            if (s_CoreLogger == nullptr)
                Init();

            return s_CoreLogger;
        }
        [[nodiscard]] static std::shared_ptr<spdlog::logger>& GetClientLogger()
        {
            if (s_ClientLogger == nullptr)
                Init();

            return s_ClientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

#define PULSARION_CORE_LOG_FATAL(...) SPDLOG_LOGGER_CRITICAL(Pulsarion::Log::GetCoreLogger(), __VA_ARGS__)
#define PULSARION_CORE_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(Pulsarion::Log::GetCoreLogger(), __VA_ARGS__)
#define PULSARION_CORE_LOG_WARN(...) SPDLOG_LOGGER_WARN(Pulsarion::Log::GetCoreLogger(), __VA_ARGS__)
#define PULSARION_CORE_LOG_INFO(...) SPDLOG_LOGGER_INFO(Pulsarion::Log::GetCoreLogger(), __VA_ARGS__)
#define PULSARION_CORE_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(Pulsarion::Log::GetCoreLogger(), __VA_ARGS__)
#define PULSARION_CORE_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(Pulsarion::Log::GetCoreLogger(), __VA_ARGS__)

#define PULSARION_LOG_FATAL(...) SPDLOG_LOGGER_CRITICAL(Pulsarion::Log::GetClientLogger(), __VA_ARGS__)
#define PULSARION_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(Pulsarion::Log::GetClientLogger(), __VA_ARGS__)
#define PULSARION_LOG_INFO(...) SPDLOG_LOGGER_INFO(Pulsarion::Log::GetClientLogger(), __VA_ARGS__)
#define PULSARION_LOG_WARN(...) SPDLOG_LOGGER_WARN(Pulsarion::Log::GetClientLogger(), __VA_ARGS__)
#define PULSARION_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(Pulsarion::Log::GetClientLogger(), __VA_ARGS__)
#define PULSARION_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(Pulsarion::Log::GetClientLogger(), __VA_ARGS__)