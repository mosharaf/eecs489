# common/CMakeLists.txt
add_library(common STATIC
    network_utils.cpp
)

# Ensure the headers in common/ are accessible
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})