#pragma once

// Define PULSARION_API macro
#ifdef PULSARION_BUILD_STATIC_LIB
#define PULSARION_API
#elif defined(PULSARION_BUILD_SHARED_LIB)
#ifdef PULSARION_BUILD_DLL
#ifdef PULSARION_PLATFORM_WINDOWS
#define PULSARION_API __declspec(dllexport)
#define PULSARION_CREATE_API(api_name)
#elif defined(PULSARION_PLATFORM_LINUX) or defined(PULSARION_PLATFORM_MACOS)
#define PULSARION_API __attribute__((visibility("default")))
#else
#error "Pulsarion only supports Windows, Linux and macOS!"
#endif
#else
#ifdef PULSARION_PLATFORM_WINDOWS
#define PULSARION_API __declspec(dllimport)
#elif defined(PULSARION_PLATFORM_LINUX) or defined(PULSARION_PLATFORM_MACOS)
#define PULSARION_API
#else
#error "Pulsarion only supports Windows, Linux and macOS!"
#endif
#endif
#else
#error "Pulsarion only supports building as static or shared library"
#endif

#ifdef PULSARION_BUILD_STATIC_LIB
#define PULSARION_DLL_EXPORT 
#define PULSARION_DLL_IMPORT
#else
#ifdef PULSARION_PLATFORM_WINDOWS
#define PULSARION_DLL_EXPORT __declspec(dllexport)
#define PULSARION_DLL_IMPORT __declspec(dllimport)
#elif defined(PULSARION_PLATFORM_LINUX) or defined(PULSARION_PLATFORM_MACOS)
#define PULSARION_DLL_EXPORT __attribute__((visibility("default")))
#define PULSARION_DLL_IMPORT
#else
#error "Pulsarion only supports Windows, Linux and macOS!"
#endif
#endif

// Define PULSARION_DEBUG_BREAK macro, which is compiler specific
#ifdef _MSC_VER  // For MSVC compiler
#define PULSARION_DEBUG_BREAK() __debugbreak();
#elif defined(__GNUC__) || defined(__clang__)  // For GCC or Clang
#define PULSARION_DEBUG_BREAK() __builtin_trap();
#else
#include <signal.h>
#define PULSARION_DEBUG_BREAK() raise(SIGTRAP);  // or some other equivalent
#endif

#if defined(PULSARION_DEBUG) || defined(PULSARION_RELEASE)
#else
#error "Pulsarion only supports Debug and Release configurations"
#endif

// Testing macros

#ifdef PULSARION_TESTING
/// If PULSARION_TESTING is defined, then PULSARION_IF_TESTING(a, b) will evaluate to a
#define PULSARION_IF_TESTING(a, b) a
#else
/// If PULSARION_TESTING is not defined, then PULSARION_IF_TESTING(a, b) will evaluate to b
#define PULSARION_IF_TESTING(a, b) b
#endif

// Include cstdint for fixed-width integer types
#include <cstdint>
