add_subdirectory(RouterLib)

add_executable(StaticRouterClient main.cpp detail/BridgeClient.cpp detail/BridgeSender.cpp detail/PCAPDumper.cpp)
target_link_libraries(StaticRouterClient PRIVATE StaticRouterLib Boost::system)

target_include_directories(StaticRouterClient PRIVATE ${CMAKE_BINARY_DIR}/proto)
