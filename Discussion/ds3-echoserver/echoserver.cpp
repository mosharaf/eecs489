#include <arpa/inet.h> //close
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO, FD_SETSIZE macros
#include <sys/types.h>
#include <unistd.h> //close

#include <cxxopts.hpp>
#include <iostream>
#include <string>

#include "network_utils.h"

/*
 * A server that echoes messages from clients.
 * You can run the server by running the standard CMake build process:
 *   $ mkdir build
 *   $ cd build
 *   $ cmake ..
 *   $ make
 * And then running the client with the following command:
 *   $ ./echoserver
 * You can also specify the port; please see the help message for more details.
 *
 * Please consult documentation for select() here:
 *      https://man7.org/linux/man-pages/man2/select.2.html
 */

int create_server_listen_socket(int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0) {
        std::cerr << "Creating server socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set master socket to allow multiple connections; this is a good habit
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
        std::cerr << "setsockopt() failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create sockaddr_in struct and set port
    sockaddr_in addr{};
    if (make_server_sockaddr(&addr, port) < 0) {
        std::cerr << "make_server_sockaddr() failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port
    if (bind(sockfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        std::cerr << "bind() failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // listen for incoming connections
    if (listen(sockfd, MAX_CLIENTS) < 0) {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Echo server listening on port " << port << std::endl;
    return sockfd;
}

void serve(int listen_sockfd) {
    std::unordered_map<int, int>
        client_socket_to_num_msgs; // map client socket to number of messages
    fd_set readfds;

    while (true) {
        // (1) Initialize the set of file descriptors (readfds)
        FD_ZERO(&readfds);               // (1.1) clear the socket set
        FD_SET(listen_sockfd, &readfds); // (1.2) add listen socket to set
        for (const auto &[client_sockfd, _] : client_socket_to_num_msgs) {
            FD_SET(client_sockfd, &readfds); // (1.3) add client socket to set
        }

        // (2) Wait for activity on any of the sockets with no timeout
        if (select(FD_SETSIZE, &readfds, nullptr, nullptr, nullptr) < 0 &&
            errno != EINTR) {
            std::cerr << "select() failed with error " << strerror(errno)
                      << std::endl;
        }
        // If we're here, that means there is activity on one of the sockets!
        // select() will block until the timeout passes or activity occurs

        // (3) Check for activity on the listen socket -- this indicates that
        // a new client is trying to connect!
        if (FD_ISSET(listen_sockfd, &readfds)) {
            sockaddr_in addr{};
            socklen_t addrlen = sizeof(addr);

            // (3.1) Accept the client connection
            int new_client_sock = accept(
                listen_sockfd, reinterpret_cast<sockaddr *>(&addr), &addrlen);
            if (new_client_sock < 0) {
                std::cerr << "accept() failed" << std::endl;
                exit(EXIT_FAILURE);
            }

            // (3.2) Add the new client socket to the map
            client_socket_to_num_msgs[new_client_sock];
            printf("\nNew client connected with ip %s on port %d "
                   "with sockfd %d\n",
                   inet_ntoa(addr.sin_addr), ntohs(addr.sin_port),
                   new_client_sock);
        }

        // (4) Check for activity on the client sockets
        // Activity on a client socket means a client is sending a message or
        // disconnecting
        for (auto it = client_socket_to_num_msgs.begin();
             it != client_socket_to_num_msgs.end();) {
            int client_sockfd = it->first;
            int &num_messages = it->second;

            if (FD_ISSET(client_sockfd, &readfds)) {
                // This file descriptor has activity!
                char buffer[MAX_MESSAGE_SIZE + 1];
                int size = recv_data_until_newline(client_sockfd, buffer);
                if (size == 0) {
                    // Client disconnected
                    printf("\n Client with sockfd %d disconnected after "
                           "sending %d messages\n",
                           client_sockfd,
                           client_socket_to_num_msgs[client_sockfd]);
                    close(client_sockfd);
                    it = client_socket_to_num_msgs.erase(it);
                } else {
                    // Echo the message back to the client
                    ++num_messages;
                    send_data(client_sockfd, std::string_view(buffer, size));
                    printf("Echoed message {%s} back to client with sockfd "
                           "%d (Message Count: %d)\n",
                           std::string(buffer, size).c_str(), client_sockfd,
                           num_messages);
                    ++it;
                }
            } else {
                // No activity on this file descriptor
                ++it;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // use cxxopts to add port option
    cxxopts::Options options("Echo Server", "An echo server");
    options.add_options()("p,port", "Port number",
                          cxxopts::value<int>()->default_value(
                              std::to_string(DEFAULT_SERVER_PORT)));

    // parse command line arguments
    auto result = options.parse(argc, argv);
    int port = result["port"].as<int>();

    int sockfd = create_server_listen_socket(port); // create server socket
    serve(sockfd);                                  // serve clients
    return 0;
}