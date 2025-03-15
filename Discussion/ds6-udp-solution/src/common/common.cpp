#include "common.h"

#include <vector>

std::expected<int, std::string> create_udp_receiver(int port) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return std::unexpected("Failed to create socket: " + std::string(strerror(errno)));
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        return std::unexpected("Failed to bind socket: " + std::string(strerror(errno)));
    }

    return sock;
}

std::expected<ssize_t, std::string> send_udp_packet(const std::string& ip, int port, const std::vector<std::byte>& packet) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return std::unexpected("Failed to create socket: " + std::string(strerror(errno)));
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    return sendto(sock, packet.data(), packet.size(), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
}
