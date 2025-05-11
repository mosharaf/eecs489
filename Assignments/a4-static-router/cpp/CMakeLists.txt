cmake_minimum_required(VERSION 3.15)
project(StaticRouter)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

include(CheckCXXSourceRuns)
include(FetchContent)

find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
    )
    FetchContent_MakeAvailable(spdlog)
endif()

find_package(Boost REQUIRED COMPONENTS system thread)

CHECK_CXX_SOURCE_RUNS("
    #include <cstdint>

    int main() {
        uint16_t test_value = 0x0100;
        uint8_t *byte_pointer = reinterpret_cast<uint8_t*>(&test_value);
        if (byte_pointer[0] == 0x00) {
            return 0;
        }
        return 1;
    }"
        IS_LITTLE_ENDIAN
)

# Define macro based on the test result
if (IS_LITTLE_ENDIAN)
    add_compile_definitions(__BYTE_ORDER=1)
else()
    add_compile_definitions(__BYTE_ORDER=2)
endif()

add_subdirectory(proto)
add_subdirectory(src)
add_subdirectory(test)