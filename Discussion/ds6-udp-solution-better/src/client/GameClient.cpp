#include "GameClient.h"

#include "common.h"
#include "spdlog/spdlog.h"

GameClient::GameClient(
    std::string ip,
    int port,
    std::function<void(PlayerUpdate)> on_player_update,
    std::function<void(GameUpdate)> on_game_update
) : client(ip, port), on_player_update(on_player_update), on_game_update(on_game_update) {}

std::expected<void, std::string> GameClient::start() {
    client.start();
    spdlog::info("GameClient started on port {}", client.get_listen_port());
    
    while (!stopped) {
        spdlog::info("Waiting for packet");
        auto packet_maybe = client.receive_packet(1024);
        if (!packet_maybe) {
            spdlog::error("Failed to receive packet: {}", packet_maybe.error());
            continue;
        }

        auto &packet = packet_maybe.value();
        spdlog::info("Received packet of size: {}", packet.size());
        UpdateType update_type = *reinterpret_cast<UpdateType*>(packet.data());
        switch (update_type) {
            case UpdateType::PLAYER_UPDATE:
                on_player_update(*reinterpret_cast<PlayerUpdate*>(packet.data() + sizeof(UpdateType)));
                break;
            case UpdateType::GAME_UPDATE:
                on_game_update(*reinterpret_cast<GameUpdate*>(packet.data() + sizeof(UpdateType)));
                break;
            default:
                spdlog::error("Unknown update type: {}", static_cast<int>(update_type));
                break;
        }
    }

    spdlog::info("GameClient stopped");
    return {};
}

void GameClient::stop() {
    stopped = true;
    client.stop();
}