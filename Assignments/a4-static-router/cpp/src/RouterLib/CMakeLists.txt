
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(StaticRouterLib STATIC ${SRCS})
target_link_libraries(StaticRouterLib proto spdlog::spdlog)

target_include_directories(StaticRouterLib SYSTEM PRIVATE ${CMAKE_BINARY_DIR}/proto)
target_include_directories(StaticRouterLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
