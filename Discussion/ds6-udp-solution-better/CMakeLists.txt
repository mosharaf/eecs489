cmake_minimum_required(VERSION 3.28)

project(discussion-06)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.1
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    GTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0
)
FetchContent_MakeAvailable(GTest)

add_subdirectory(src)
add_subdirectory(test)