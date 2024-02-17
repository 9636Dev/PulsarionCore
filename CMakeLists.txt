cmake_minimum_required(VERSION 3.27)
project(PulsarionCore VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "Contains Core and Utility classes for Pulsarion")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED PULSARION_LIBRARY_TYPE)
    set(PULSARION_LIBRARY_TYPE "STATIC" CACHE STRING "Type of library to build, static or shared")
endif()
MESSAGE(NOTICE "Building Pulsarion for type: ${PULSARION_LIBRARY_TYPE}")

if (NOT DEFINED PULSARION_RENDERER)
    set(PULSARION_RENDERER "OpenGL" CACHE STRING "Type of renderer to use, OpenGL, Metal, DirectX12 or Vulkan")
endif()
MESSAGE(NOTICE "Building Pulsarion for renderer: ${PULSARION_RENDERER}")

add_subdirectory(vendor/spdlog) # SpdLog

set(PULSARION_CORE_SOURCES
        src/PulsarionCore/Log.hpp
        src/PulsarionCore/Log.cpp
        src/PulsarionCore/Core.hpp
        src/PulsarionCore/Core.hpp
        src/PulsarionCore/Assert.hpp
        src/PulsarionCore/Utility.hpp # Contains utility classes
        src/PulsarionCore/File.hpp
        src/PulsarionCore/File.cpp
)
add_library(PulsarionCore ${PULSARION_LIBRARY_TYPE} ${PULSARION_CORE_SOURCES})

if (PULSARION_LIBRARY_TYPE STREQUAL "STATIC")
    target_compile_definitions(PulsarionCore PUBLIC "PULSARION_BUILD_STATIC_LIB")
elseif (PULSARION_LIBRARY_TYPE STREQUAL "SHARED")
    target_compile_definitions(PulsarionCore PUBLIC "PULSARION_BUILD_SHARED_LIB")
    target_compile_definitions(PulsarionCore PRIVATE "PULSARION_BUILD_DLL")
endif()

target_compile_definitions(PulsarionCore PUBLIC
        $<$<PLATFORM_ID:Windows>:PULSARION_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:PULSARION_PLATFORM_LINUX>
        $<$<PLATFORM_ID:Darwin>:PULSARION_PLATFORM_MACOS>
        $<$<CONFIG:Debug>:PULSARION_DEBUG>
        $<$<CONFIG:Release>:PULSARION_RELEASE>
        $<$<CONFIG:RelWithDebInfo>:PULSARION_RELEASE>
        $<$<CONFIG:MinSizeRel>:PULSARION_RELEASE>
)


if (PULSARION_RENDERER STREQUAL "OpenGL")
    target_compile_definitions(PulsarionCore PUBLIC PULSARION_RENDERER_OPENGL)
elseif (PULSARION_RENDERER STREQUAL "Metal")
    target_compile_definitions(PulsarionCore PUBLIC PULSARION_RENDERER_METAL)
elseif (PULSARION_RENDERER STREQUAL "DirectX12")
    target_compile_definitions(PulsarionCore PUBLIC PULSARION_RENDERER_DIRECTX12)
elseif (PULSARION_RENDERER STREQUAL "Vulkan")
    target_compile_definitions(PulsarionCore PUBLIC PULSARION_RENDERER_VULKAN)
endif()


target_link_libraries(PulsarionCore PUBLIC spdlog::spdlog)

target_include_directories(PulsarionCore PUBLIC src)

