#include <arpa/inet.h> // ntohs()
#include <cstdlib>
#include <stdio.h>  // printf(), perror()
#include <stdlib.h> // atoi()
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h> // socket(), connect(), send(), recv()
#include <unistd.h>     // close()

#include <cxxopts.hpp>
#include <format>
#include <iostream>

#include "network_utils.h"

/*
 * A client that sends a given message to the server every MESSAGE_INTERVAL_S
 * seconds. You can run the client by running the standard CMake build process:
 *   $ mkdir build
 *   $ cd build
 *   $ cmake ..
 *   $ make
 * And then running the client with the following command:
 *   $ ./client --m "Hello from Client A"
 * You can also specify the hostname and port; please see the help message for
 * more details.
 */

const unsigned int MESSAGE_INTERVAL_S = 2;

/*
 * Sets up a socket for communication with the server. Returns the sockfd.
 */
int set_up_socket(const char *hostname, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    if (make_client_sockaddr(&addr, hostname, port) == -1) {
        std::cerr << "Error making client sockaddr" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1) {
        std::cerr << "Error connecting stream socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server at " << hostname << " on port " << port
              << std::endl;

    return sockfd;
}

/**
 * Sends a string message to the server.
 *
 * Parameters:
 *		hostname: 	Remote hostname of the server.
 *		port: 		Remote port of the server.
 * 		message: 	The message to send, as a C-string.
 * Returns:
 *		0 on success, -1 on failure.
 */
int send_messages(int sockfd, std::string &message) {
    std::cout << "Sending message to server: " << message << std::endl;
    char buffer[MAX_MESSAGE_SIZE + 1];

    for (unsigned int i = 0; i < 60; i++) {
        ssize_t sval = send_data(sockfd, message + "\n");
        if (sval < 0) {
            std::cerr << "Error sending message" << std::endl;
            return -1;
        }

        std::cout << std::format(
                         "\nSent message \"{}\" to server for the {}th time",
                         message, i)
                  << std::endl;

        ssize_t rval = recv(sockfd, buffer, message.size(), MSG_WAITALL);
        if (rval < 0) {
            std::cerr << "Error receiving message" << std::endl;
            return -1;
        }
        std::cout << std::format("Received message \"{}\" from server",
                                 std::string(buffer, rval))
                  << std::endl;

        sleep(2);
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    // use cxxopts to add hostname, port, time options
    cxxopts::Options options(
        "client", "A client that sends one message per second to the server.");
    options.add_options()(
        "h,hostname", "Remote hostname of the server",
        cxxopts::value<std::string>()->default_value("localhost"))(
        "p,port", "Remote port of the server",
        cxxopts::value<int>()->default_value(
            std::to_string(DEFAULT_SERVER_PORT)))(
        "m,message", "The message to send", cxxopts::value<cxxopts::String>());

    // Print help if no arguments are passed
    if (argc == 1) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    // Parse options
    auto result = options.parse(argc, argv);
    const char *hostname = result["hostname"].as<std::string>().c_str();
    int port = result["port"].as<int>();
    std::string message = result["message"].as<cxxopts::String>();

    if (message.size() > MAX_MESSAGE_SIZE) {
        std::cerr << "Message is too long; max size is " << MAX_MESSAGE_SIZE
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    if (message.find('\n') != std::string::npos) {
        std::cerr << "Message cannot contain newline characters" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto sockfd = set_up_socket(hostname, port);
    send_messages(sockfd, message);

    return 0;
}