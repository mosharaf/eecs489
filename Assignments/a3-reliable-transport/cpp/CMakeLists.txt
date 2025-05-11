cmake_minimum_required(VERSION 3.28)
project(eecs489-project3-wn25)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Ensure that output executables are in the build/bin directory
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

# Fetch the required dependencies
include(FetchContent)

find_package(spdlog QUIET)
if (NOT spdlog_FOUND)
        message(STATUS "Fetching spdlog")
        FetchContent_Declare(
                spdlog
                GIT_REPOSITORY https://github.com/gabime/spdlog.git
                GIT_TAG v1.14.1
        )
        FetchContent_MakeAvailable(spdlog)
endif()

find_package(cxxopts QUIET)
if (NOT cxxopts_FOUND)
        message(STATUS "Fetching cxxopts")
        FetchContent_Declare(cxxopts
                GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
                GIT_TAG master
        )
        FetchContent_MakeAvailable(cxxopts)
endif()

find_package(Boost REQUIRED COMPONENTS regex)

# Recurse through the subdirectories
add_subdirectory(src)