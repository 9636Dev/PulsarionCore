#include "Log.hpp"

#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Pulsarion {
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        static bool s_Initialized = false;
        if (s_Initialized)
            return;
        s_Initialized = true;
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("PULSARION");
        s_CoreLogger->set_level(spdlog::level::trace);

        auto formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->set_pattern("%^[%T] %s:%# [%n] %v%$");
        s_CoreLogger->set_formatter(std::move(formatter));

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);

        formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->set_pattern("%^[%T] %s:%# [%n] %v%$");
        s_ClientLogger->set_formatter(std::move(formatter));
    }
}