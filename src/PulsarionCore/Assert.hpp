#pragma once

#include "Core.hpp" // Required for PULSARION_DEBUG_BREAK
#include "Log.hpp" // Required for asserts

#ifdef PULSARION_DEBUG
#define PULSARION_INTERNAL_ASSERT_WITH_MSG(x, msg, ...) \
    if (!(x)) { \
        PULSARION_CORE_LOG_ERROR("Assertion Failed at " __FILE__ ":{0}: {1}", __LINE__, msg); \
        PULSARION_DEBUG_BREAK(); \
    }
#define PULSARION_ASSERT(...) PULSARION_INTERNAL_ASSERT_WITH_MSG(__VA_ARGS__, "No message provided")
#define PULSARION_RUN_IF_DEBUG(...) do { __VA_ARGS__; } while (false)
#else
#define PULSARION_ASSERT(x, ...) ((void)0)
#define PULSARION_RUN_IF_DEBUG(...) ((void)0)
#endif