#pragma once

#include <expected>
#include <string>
#include <functional>
#include <atomic>

#include "GameTypes.h"
#include "common.h"
class GameClient {
    public:
        /**
         * Constructs a new GameClient
         * @param port The port to listen on
         * @param on_player_update A function to call when a player update is received
         * @param on_game_update A function to call when a game update is received
         */
        GameClient(
            std::string ip,
            int port,
            std::function<void(PlayerUpdate)> on_player_update,
            std::function<void(GameUpdate)> on_game_update
        );
        /**
         * Starts the client
         * @return An expected value containing an error string if the client fails to start, or void if it starts successfully
         */
        std::expected<void, std::string> start();
        /**
         * Stops the client
         */
        void stop();
    private:
        std::function<void(PlayerUpdate)> on_player_update;
        std::function<void(GameUpdate)> on_game_update;
        
        UDPClient client;

        std::atomic<bool> stopped = false;
};