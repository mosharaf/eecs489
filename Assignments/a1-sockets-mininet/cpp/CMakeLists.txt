cmake_minimum_required(VERSION 3.10)

PROJECT(EECS489A1)
SET(CMAKE_CXX_STANDARD 23)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(FetchContent)

find_package(spdlog)
find_package(cxxopts)

if(NOT spdlog_FOUND)
    message(STATUS "Fetching spdlog")
    FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG v1.14.1
    )
    FetchContent_MakeAvailable(spdlog)
endif()

if (NOT cxxopts_FOUND)
    message(STATUS "Fetching cxxopts")
    FetchContent_Declare(cxxopts
            GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(cxxopts)
endif()

add_subdirectory(src)