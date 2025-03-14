#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

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
  
/**
 * Creates a UDP receiver
 * @param port The port to listen on
 * @return An expected value containing an error string if the receiver fails to create, or the socket file descriptor if it creates successfully
 */
std::expected<int, std::string> create_udp_receiver(int port);
/**
 * Sends a UDP packet
 * @param ip The IP address to send the packet to
 * @param port The port to send the packet to
 * @param packet The packet to send
 * @return An expected value containing an error string if the packet fails to send, or the number of bytes sent if it sends successfully
 */
std::expected<ssize_t, std::string> send_udp_packet(const std::string& ip, int port, const std::vector<std::byte>& packet);