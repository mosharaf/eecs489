#pragma once

#include <string>
#include <expected>
#include "GameTypes.h"

class GameServer {
    public:
        GameServer(int port);
        ~GameServer();
        /**
         * Stops the server
         */
        void stop();
        /**
         * Starts the server
         * @return An expected value containing an error string if the server fails to start, or void if it starts successfully
         */
        std::expected<void, std::string> start();
        /**
         * Sends a player update to the server
         * @param ip The IP address of the client
         * @param port The port of the client
         * @param id The ID of the player
         * @param position The position of the player
         * @param health The health of the player
         * @return An expected value containing an error string if the update fails to send, or void if it sends successfully
         */
        std::expected<void, std::string> send_player_update(std::string ip, uint16_t port, int id, Position position, int health);
        /**
         * Sends a game update to the server
         * @param ip The IP address of the client
         * @param port The port of the client
         * @param id The ID of the player
         * @param time_left The time left in the game
         */
        std::expected<void, std::string> send_game_update(std::string ip, uint16_t port, int id, int time_left);
    private:
        int port;
        int recv_socket;
};
