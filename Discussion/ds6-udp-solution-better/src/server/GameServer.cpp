#include "GameServer.h"

#include <vector>

#include "spdlog/spdlog.h"
#include "common.h"

GameServer::GameServer(std::string ip, uint16_t port) : client(ip, port) {}

std::expected<void, std::string> GameServer::start() {
    client.start();
    spdlog::info("GameServer started on port {}", client.get_listen_port());

    return {};
}

GameServer::~GameServer() {
    stop();
}

void GameServer::stop() {
    client.stop();
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

    auto sender_socket = EXPECT_OK(client.send_packet(ip, port, packet));
    spdlog::info("Sent player update to {}:{}", ip, port);
    return {};
}

std::expected<void, std::string> GameServer::send_game_update(std::string ip, uint16_t port, int id, int time_left) {
    std::vector<std::byte> packet;

    GameUpdate game_update = {
        .id = id,
        .time_left = time_left
    };

    packet.push_back(std::byte(UpdateType::GAME_UPDATE));
    packet.insert(
        packet.end(), 
        reinterpret_cast<const std::byte*>(&game_update), reinterpret_cast<const std::byte*>(&game_update) + sizeof(game_update));

    auto sender_socket = EXPECT_OK(client.send_packet(ip, port, packet));
    spdlog::info("Sent game update to {}:{}", ip, port);
    return {};
}