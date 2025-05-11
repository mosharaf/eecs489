#include "GameServer.h"

#include <vector>

#include "spdlog/spdlog.h"
#include "common.h"

GameServer::GameServer(int port) : port(port) {}

std::expected<void, std::string> GameServer::start() {
    auto recv_socket = EXPECT_OK(create_udp_receiver(port));
    spdlog::info("GameServer started on port {}", port);

    return {};
}

GameServer::~GameServer() {
    stop();
}

void GameServer::stop() {
    close(recv_socket);
}

std::expected<void, std::string> GameServer::send_player_update(std::string ip, uint16_t port, int id, Position position, int health) {
    std::vector<std::byte> packet;

    PlayerUpdate player_update = {
        .id = id,
        .position = position,
        .health = health
    };

    packet.push_back(std::byte(UpdateType::PLAYER_UPDATE));
    packet.insert(
        packet.end(), 
        reinterpret_cast<const std::byte*>(&player_update), reinterpret_cast<const std::byte*>(&player_update) + sizeof(player_update));

    auto sender_socket = EXPECT_OK(send_udp_packet(ip, port, packet));
    spdlog::info("Sent player update to {}:{}", ip, port);
    return {};
}

std::expected<void, std::string> GameServer::send_game_update(std::string ip, uint16_t port, int id, int time_left) {
    // TODO: Implement the send_game_update function
    return {};
}