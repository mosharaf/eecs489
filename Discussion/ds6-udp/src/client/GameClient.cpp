#include "GameClient.h"

#include "common.h"
#include "spdlog/spdlog.h"

GameClient::GameClient(
    int port,
    std::function<void(PlayerUpdate)> on_player_update,
    std::function<void(GameUpdate)> on_game_update
) : port(port), on_player_update(on_player_update), on_game_update(on_game_update) {}

std::expected<void, std::string> GameClient::start() {
    recv_socket = EXPECT_OK(create_udp_receiver(port));
    spdlog::info("GameClient started on port {}", port);
    
    while (!stopped) {
        // TODO: Implement the client loop
    }

    close(recv_socket);
    spdlog::info("GameClient stopped");
    return {};
}

void GameClient::stop() {
    stopped = true;
    close(recv_socket);
}