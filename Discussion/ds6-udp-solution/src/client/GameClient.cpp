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
        std::vector<std::byte> packet(1024);
        auto bytes_received = recvfrom(recv_socket, packet.data(), packet.size(), 0, nullptr, nullptr);

        UpdateType update_type = *reinterpret_cast<UpdateType*>(packet.data());
        if (bytes_received < 0) {
            spdlog::error("Error receiving update type: {}", strerror(errno));
            continue;
        }
        switch (update_type) {
            case UpdateType::PLAYER_UPDATE: {
                PlayerUpdate player_update = *reinterpret_cast<PlayerUpdate*>(packet.data() + sizeof(UpdateType));
                if (bytes_received < 0) {
                    spdlog::error("Error receiving player update: {}", strerror(errno));
                    continue;
                }
                
                player_update.id = ntohl(player_update.id);
                player_update.position.x = ntohl(player_update.position.x);
                player_update.position.y = ntohl(player_update.position.y);
                player_update.health = ntohl(player_update.health);
                
                on_player_update(player_update);
                break;
            }
            case UpdateType::GAME_UPDATE: {
                GameUpdate game_update = *reinterpret_cast<GameUpdate*>(packet.data() + sizeof(UpdateType));
                if (bytes_received < 0) {
                    spdlog::error("Error receiving game update: {}", strerror(errno));
                    continue;
                }

                game_update.id = ntohl(game_update.id);
                game_update.time_left = ntohl(game_update.time_left);

                on_game_update(game_update);
                break;
            }
            default: {
                spdlog::error("Unknown update type: {}", static_cast<int>(update_type));
                break;
            }
        }
    }

    close(recv_socket);
    spdlog::info("GameClient stopped");
    return {};
}

void GameClient::stop() {
    stopped = true;
    close(recv_socket);
}