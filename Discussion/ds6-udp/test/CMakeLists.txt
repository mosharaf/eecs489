set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

add_executable(GameServerTest GameTest.cpp)

target_include_directories(GameServerTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(GameServerTest PRIVATE 
    GameServer
    GameClient
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(GameServerTest)