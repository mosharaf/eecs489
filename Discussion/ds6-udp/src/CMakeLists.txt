add_library(common common/common.cpp common/GameTypes.h)

add_library(GameServer server/GameServer.cpp server/GameServer.h)
add_library(GameClient client/GameClient.cpp client/GameClient.h)

target_include_directories(GameServer PUBLIC common)
target_include_directories(GameClient PUBLIC common)

target_link_libraries(GameServer common spdlog::spdlog)
target_link_libraries(GameClient common spdlog::spdlog)