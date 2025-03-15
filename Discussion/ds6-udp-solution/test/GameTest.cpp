#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>

#include "client/GameClient.h"
#include "server/GameServer.h"
#include "common/GameTypes.h"
#include "spdlog/spdlog.h"

// Custom logger for capturing log output
class TestLogger {
public:
    static void setup() {
        spdlog::set_pattern("[%l] %v");
        spdlog::set_level(spdlog::level::info);
    }

    static std::string formatPlayerUpdate(const PlayerUpdate& update) {
        std::stringstream ss;
        ss << "Received PlayerUpdate packet: {Player ID: " << update.id 
           << ", Position: (" << update.position.x << ", " << update.position.y 
           << "), Health: " << update.health << "}";
        return ss.str();
    }

    static std::string formatGameUpdate(const GameUpdate& update) {
        std::stringstream ss;
        ss << "Received GameUpdate packet: {Game ID: " << update.id 
           << ", Time Left: " << update.time_left << "}";
        return ss.str();
    }
};

// Test fixture for GameServer and GameClient integration tests
class GameIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        TestLogger::setup();
        
        // Use different ports for server and client to avoid conflicts
        server_port = next_unused_port++;
        client_port = next_unused_port++;
        
        // Create server and client
        server = std::make_unique<GameServer>(server_port);
        
        // Setup client with callbacks that store received updates
        client = std::make_unique<GameClient>(
            client_port,
            [this](PlayerUpdate update) {
                std::lock_guard<std::mutex> lock(mutex);
                player_updates.push(update);
                spdlog::info(TestLogger::formatPlayerUpdate(update));
                cv.notify_one();
            },
            [this](GameUpdate update) {
                std::lock_guard<std::mutex> lock(mutex);
                game_updates.push(update);
                spdlog::info(TestLogger::formatGameUpdate(update));
                cv.notify_one();
            }
        );
    }

    void TearDown() override {
        // Stop client and server
        if (client) {
            client->stop();
        }

        if (server) {
            server->stop();
        }
        
        // Join threads if they're running
        if (server_thread.joinable()) {
            server_thread.join();
        }
        spdlog::info("Server thread joined");
        if (client_thread.joinable()) {
            client_thread.join();
        }
        spdlog::info("Client thread joined");
    }

    // Helper method to start server and client in separate threads
    void startServerAndClient() {
        // Start server in a separate thread
        server_thread = std::thread([this]() {
            auto result = server->start();
            ASSERT_TRUE(result.has_value()) << result.error();
        });

        // Start client in a separate thread
        client_thread = std::thread([this]() {
            auto result = client->start();
            ASSERT_TRUE(result.has_value()) << result.error();
        });

        // Give some time for server and client to start
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Helper method to wait for updates with timeout
    template<typename T>
    bool waitForUpdate(std::queue<T>& queue, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex);
        return cv.wait_for(lock, timeout, [&queue]() { return !queue.empty(); });
    }

    // Helper method to get the next update from the queue
    template<typename T>
    T getNextUpdate(std::queue<T>& queue) {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) {
            throw std::runtime_error("No updates available");
        }
        T update = queue.front();
        queue.pop();
        return update;
    }

    inline static int next_unused_port = 8000;

    std::unique_ptr<GameServer> server;
    std::unique_ptr<GameClient> client;
    int server_port; 
    int client_port;
    
    std::thread server_thread;
    std::thread client_thread;
    
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<PlayerUpdate> player_updates;
    std::queue<GameUpdate> game_updates;
};

// Test sending and receiving a player update
TEST_F(GameIntegrationTest, PlayerUpdateTest) {
    startServerAndClient();
    
    // Send a player update from server to client
    Position pos = {10, 20};
    auto ok = server->send_player_update("127.0.0.1", client_port, 1, pos, 100);
    ASSERT_TRUE(ok.has_value()) << ok.error();
    // Wait for the client to receive the update
    ASSERT_TRUE(waitForUpdate(player_updates, std::chrono::seconds(2)));
    
    // Verify the received update
    PlayerUpdate update = getNextUpdate(player_updates);
    EXPECT_EQ(update.id, 1);
    EXPECT_EQ(update.position.x, 10);
    EXPECT_EQ(update.position.y, 20);
    EXPECT_EQ(update.health, 100);
}

// Test sending and receiving a game update
TEST_F(GameIntegrationTest, GameUpdateTest) {
    startServerAndClient();
    
    // Send a game update from server to client
    auto ok = server->send_game_update("127.0.0.1", client_port, 1, 100);
    ASSERT_TRUE(ok.has_value()) << ok.error();
    
    // Wait for the client to receive the update
    ASSERT_TRUE(waitForUpdate(game_updates, std::chrono::seconds(2)));
    // Verify the received update
    GameUpdate update = getNextUpdate(game_updates);
    EXPECT_EQ(update.id, 1);
    EXPECT_EQ(update.time_left, 100);
}

// Test sending multiple updates in sequence
TEST_F(GameIntegrationTest, MultipleUpdatesTest) {
    startServerAndClient();
    
    // Send multiple player updates
    Position pos1 = {10, 20};
    Position pos2 = {30, 40};
    auto ok1 = server->send_player_update("127.0.0.1", client_port, 1, pos1, 100);
    auto ok2 = server->send_player_update("127.0.0.1", client_port, 2, pos2, 75);
    ASSERT_TRUE(ok1.has_value()) << ok1.error();
    ASSERT_TRUE(ok2.has_value()) << ok2.error();
    
    // Send a game update
    auto ok3 = server->send_game_update("127.0.0.1", client_port, 1, 100);
    ASSERT_TRUE(ok3.has_value()) << ok3.error();
    
    // Wait for all updates to be received
    ASSERT_TRUE(waitForUpdate(player_updates, std::chrono::seconds(2)));
    ASSERT_TRUE(waitForUpdate(player_updates, std::chrono::seconds(2)));
    ASSERT_TRUE(waitForUpdate(game_updates, std::chrono::seconds(2)));
    
    // Verify player updates
    PlayerUpdate player_update1 = getNextUpdate(player_updates);
    EXPECT_EQ(player_update1.id, 1);
    EXPECT_EQ(player_update1.position.x, 10);
    EXPECT_EQ(player_update1.position.y, 20);
    EXPECT_EQ(player_update1.health, 100);
    
    PlayerUpdate player_update2 = getNextUpdate(player_updates);
    EXPECT_EQ(player_update2.id, 2);
    EXPECT_EQ(player_update2.position.x, 30);
    EXPECT_EQ(player_update2.position.y, 40);
    EXPECT_EQ(player_update2.health, 75);
    
    // Verify game update
    GameUpdate game_update = getNextUpdate(game_updates);
    EXPECT_EQ(game_update.id, 1);
    EXPECT_EQ(game_update.time_left, 100);
}
