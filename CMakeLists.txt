cmake_minimum_required(VERSION 3.15)
project(endstone LANGUAGES CXX)

# -----------------------
# C++ Standard
# -----------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# -----------------------
# Compiler Checks
# -----------------------
if (WIN32)
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        message(FATAL_ERROR "Endstone: MSVC is required on Windows.")
    endif ()
elseif (UNIX)
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Endstone: Clang is required on Linux.")
    endif ()
    # Force libc++ for ABI compatibility
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fPIC" CACHE STRING "" FORCE)
else ()
    message(FATAL_ERROR "Endstone: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_PROCESSOR}) is not supported")
endif ()

# -----------------------
# Options
# -----------------------
option(CODE_COVERAGE "Enable code coverage reporting" OFF)
option(ENDSTONE_ENABLE_DEVTOOLS "Build Endstone with DevTools enabled." OFF)
option(ENDSTONE_SEPARATE_DEBUG_INFO "Separate debug info into .dbg files on Linux using objcopy" OFF)

# -----------------------
# FetchContent for Dependencies
# -----------------------
include(FetchContent)

# pybind11
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1
)
FetchContent_MakeAvailable(pybind11)

# tomlplusplus
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.2.0
)
FetchContent_MakeAvailable(tomlplusplus)

# fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.2.0
)
FetchContent_MakeAvailable(fmt)

# -----------------------
# Endstone header-only API
# -----------------------
add_subdirectory(include)

if (NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    return()
endif ()

# -----------------------
# Implementations
# -----------------------
add_subdirectory(third_party)
add_subdirectory(src/endstone/python)
add_subdirectory(src/bedrock)
add_subdirectory(src/endstone/core)
add_subdirectory(src/endstone/runtime)

# -----------------------
# Tests
# -----------------------
if (NOT BUILD_TESTING STREQUAL OFF)
    enable_testing()

    if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage")
    endif ()

    # GTest
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.15.0
    )
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
    add_subdirectory(tests)
endif ()
