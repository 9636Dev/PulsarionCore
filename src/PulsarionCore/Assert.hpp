#pragma once

#include "Core.hpp" // Required for PULSARION_DEBUG_BREAK
#include "Log.hpp" // Required for asserts

#ifdef PULSARION_DEBUG
#define PULSARION_ASSERT(x, msg) \
    { \
        auto condition = (x); \
        if (!(condition)) { \
            PULSARION_CORE_LOG_ERROR("Assertion Failed at " __FILE__ ":{0}: {1}", __LINE__, msg); \
            PULSARION_DEBUG_BREAK(); \
        } \
    }
#define PULSARION_RUN_IF_DEBUG(...) do { __VA_ARGS__; } while (false)
#else
#define PULSARION_ASSERT(x, ...) { (void)(x); } 
// We do this so that functions with [[nodiscard]] wont warn 
#define PULSARION_RUN_IF_DEBUG(...) ((void)0)
#endif
