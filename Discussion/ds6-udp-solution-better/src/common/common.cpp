#include "common.h"

#include <vector>

UDPClient::UDPClient(std::string listen_ip, int listen_port) : listen_ip(listen_ip), listen_port(listen_port) {}

UDPClient::~UDPClient() {
    stop();
}

void UDPClient::start() {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(listen_ip.c_str());
    server_addr.sin_port = htons(listen_port);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Failed to bind socket");
    }
}

void UDPClient::stop() {
    stopped = true;
    close(socket_fd);
}

std::expected<ssize_t, std::string> UDPClient::send_packet(std::string ip, int port, const std::vector<std::byte>& packet) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port = htons(port);

    return sendto(socket_fd, packet.data(), packet.size(), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
}

std::expected<std::vector<std::byte>, std::string> UDPClient::receive_packet(ssize_t max_size) {
    std::vector<std::byte> buffer(max_size);
    
    ssize_t bytes_received = recvfrom(socket_fd, buffer.data(), max_size, 0, nullptr, nullptr);
    if (bytes_received < 0) {
        if (stopped) {
            return std::unexpected("UDPClient stopped");
        }

        return std::unexpected(strerror(errno));
    }

    buffer.resize(bytes_received);
    return buffer;
}
