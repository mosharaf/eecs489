cmake_minimum_required(VERSION 3.10) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(489Discussion3)

include(FetchContent)
find_package(cxxopts)

if (NOT cxxopts_FOUND)
    message(STATUS "Fetching cxxopts")
    FetchContent_Declare(cxxopts
            GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(cxxopts)
endif()

add_executable(echoserver echoserver.cpp network_utils.cpp) 
add_executable(client client.cpp network_utils.cpp) 

target_link_libraries(echoserver cxxopts::cxxopts)
target_link_libraries(client cxxopts::cxxopts)