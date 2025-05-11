#include <arpa/inet.h>       // inet_ntoa
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>        // FD_SET, FD_ISSET, FD_ZERO macros
#include <unistd.h>          // close
#include <cerrno>
#include <csignal>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

// Third-party options parser
#include <cxxopts.hpp>

// External network helper functions (make sure these are defined in your project)
#include "network_utils.h"

// Default port defined somewhere in your project (or define it here)
#ifndef DEFAULT_SERVER_PORT
#define DEFAULT_SERVER_PORT 8080
#endif

#ifndef MAX_CLIENTS
#define MAX_CLIENTS 10
#endif

#ifndef MAX_MESSAGE_SIZE
#define MAX_MESSAGE_SIZE 1024
#endif

class EchoServer {
public:
    /// Constructs an echo server that listens on the given port.
    explicit EchoServer(int port)
        : listen_sockfd_{-1} {
        initialize_listen_socket(port);
    }

    /// Closes the listening socket and any open client sockets.
    ~EchoServer() {
        // Close client sockets
        for (const auto &entry : client_msg_counts_) {
            close(entry.first);
        }
        // Close listening socket
        if (listen_sockfd_ != -1) {
            close(listen_sockfd_);
        }
    }

    /// Runs the server loop to accept and echo client messages.
    void run() {
        std::cout << "Echo server listening on port " << port_ << std::endl;
        while (true) {
            fd_set readfds;
            FD_ZERO(&readfds);

            // Add the listening socket to the set.
            FD_SET(listen_sockfd_, &readfds);

            // Add client sockets to the set.
            for (const auto &entry : client_msg_counts_) {
                FD_SET(entry.first, &readfds);
            }

            // Wait for activity on any socket.
            int activity = select(FD_SETSIZE, &readfds, nullptr, nullptr, nullptr);
            if (activity < 0 && errno != EINTR) {
                std::cerr << "select() failed: " << std::strerror(errno)
                          << std::endl;
                continue;
            }

            // Check if there's a new connection.
            if (FD_ISSET(listen_sockfd_, &readfds)) {
                accept_new_client();
            }

            // Handle activity on client sockets.
            handle_client_activity(readfds);
        }
    }

private:
    int listen_sockfd_;
    int port_;
    // Map from client socket to number of messages received.
    std::unordered_map<int, int> client_msg_counts_;

    /// Initializes the listening socket on the given port.
    void initialize_listen_socket(int port) {
        port_ = port;
        listen_sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_sockfd_ < 0) {
            std::cerr << "Error creating server socket: "
                      << std::strerror(errno) << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Allow reuse of the address.
        int yes = 1;
        if (setsockopt(listen_sockfd_, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(yes)) < 0) {
            std::cerr << "setsockopt() failed: " << std::strerror(errno)
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Create and initialize the server address.
        sockaddr_in addr{};
        if (make_server_sockaddr(&addr, port) < 0) {
            std::cerr << "make_server_sockaddr() failed" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Bind the socket to the port.
        if (bind(listen_sockfd_, reinterpret_cast<sockaddr *>(&addr),
                 sizeof(addr)) < 0) {
            std::cerr << "bind() failed: " << std::strerror(errno)
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Start listening.
        if (listen(listen_sockfd_, MAX_CLIENTS) < 0) {
            std::cerr << "listen() failed: " << std::strerror(errno)
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    /// Accepts a new client connection.
    void accept_new_client() {
        sockaddr_in client_addr{};
        socklen_t addr_len = sizeof(client_addr);
        int client_sockfd = accept(
            listen_sockfd_, reinterpret_cast<sockaddr *>(&client_addr),
            &addr_len);
        if (client_sockfd < 0) {
            std::cerr << "accept() failed: " << std::strerror(errno)
                      << std::endl;
            return;
        }

        // Add new client to the map with initial message count 0.
        client_msg_counts_.emplace(client_sockfd, 0);
        std::printf("\nNew client connected with IP %s on port %d (sockfd %d)\n",
                    inet_ntoa(client_addr.sin_addr),
                    ntohs(client_addr.sin_port), client_sockfd);
    }

    /// Checks all client sockets for activity and echoes messages back.
    void handle_client_activity(fd_set &readfds) {
        // Use an iterator to allow safe removal during iteration.
        for (auto it = client_msg_counts_.begin();
             it != client_msg_counts_.end();) {
            int client_sockfd = it->first;
            int &num_messages = it->second;

            if (FD_ISSET(client_sockfd, &readfds)) {
                char buffer[MAX_MESSAGE_SIZE + 1]{};
                int bytes_received =
                    recv_data_until_newline(client_sockfd, buffer);
                if (bytes_received == 0) {
                    // Client disconnected.
                    std::printf("\nClient (sockfd %d) disconnected after "
                                "sending %d messages\n",
                                client_sockfd, num_messages);
                    close(client_sockfd);
                    it = client_msg_counts_.erase(it);
                    continue;
                } else {
                    ++num_messages;
                    // Echo back the received message.
                    send_data(client_sockfd,
                              std::string_view(buffer, bytes_received));
                    std::printf("Echoed message {%.*s} back to client (sockfd %d, Message Count: %d)\n",
                                bytes_received, buffer, client_sockfd, num_messages);
                }
            }
            ++it;
        }
    }
};

int main(int argc, char *argv[]) {
    // Parse command-line options using cxxopts.
    cxxopts::Options options("EchoServer", "A simple echo server");
    options.add_options()
        ("p,port", "Port number", cxxopts::value<int>()->default_value(
                                        std::to_string(DEFAULT_SERVER_PORT)))
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    int port = result["port"].as<int>();

    // Create and run the echo server.
    EchoServer server(port);
    server.run();

    return 0;
}
