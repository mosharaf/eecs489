#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <atomic>
#include <expected>
#include <string>
/**
 * Macro to reduce boilerplate code for error handling
 * Instead of writing:
 * auto result_maybe = expr;
 * if (!result_maybe) {
 *     spdlog::error("Error: {}", result_maybe.error());
 *     return std::unexpected(result_maybe.error());
 * }
 * auto result = *result_maybe;
 * 
 * You can write:
 * auto result = EXPECT_OK(expr);
 */
#define EXPECT_OK(expr)                                                 \
  ({                                                                    \
    auto _result = (expr);                                              \
    if (!_result) {                                                     \
      spdlog::error("Error: {}", _result.error());                      \
      return std::unexpected(_result.error());                          \
    }                                                                   \
    *_result;                                                           \
  })
  
class UDPClient {
  public:
    /**
     * Creates a UDP client
     * @param ip The IP address to send and receive packets on
     * @param port The port to send and receive packets on
     */
    UDPClient(std::string listen_ip, int listen_port);
    ~UDPClient();

    void start();
    void stop();

    /**
     * Sends a UDP packet
     * @param packet The packet to send
     * @return An expected value containing an error string if the packet fails to send, or void if it sends successfully
     */
    std::expected<ssize_t, std::string> send_packet(std::string ip, int port, const std::vector<std::byte>& packet);
    /**
     * Receives a UDP packet
     * @param max_size The maximum size of the packet to receive
     * @return An expected value containing an error string if the packet fails to receive, or the packet if it receives successfully
     */
    std::expected<std::vector<std::byte>, std::string> receive_packet(ssize_t max_size);

    int get_listen_port() const { return listen_port; }
    std::string get_listen_ip() const { return listen_ip; }
  private:
    int socket_fd;
    std::string listen_ip;
    int listen_port;

    std::atomic<bool> stopped = false;
};
