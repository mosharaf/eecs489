#include "network_utils.h"

#include <stdio.h>      // perror(), fprintf()
#include <string.h>     // memcpy()
#include <sys/socket.h> // getsockname(), send()
#include <unistd.h>     // close()

int make_server_sockaddr(struct sockaddr_in *addr, int port) {
    // (1) This is an Internet socket
    addr->sin_family = AF_INET;
    // (2) Server sockets listen; let the OS figure out the IP addres
    addr->sin_addr.s_addr = INADDR_ANY;
    // (3) Tell the socket to listen on the specified port
    addr->sin_port = htons(port);
    return 0;
}

int make_client_sockaddr(struct sockaddr_in *addr, const char *hostname,
                         int port) {
    // (1) This is an Internet socket
    addr->sin_family = AF_INET;

    // (2) Figure out the hostname, and assign it to the socket
    struct hostent *host = gethostbyname(hostname);
    if (host == nullptr) {
        fprintf(stderr, "%s: unknown host\n", hostname);
        return -1;
    }
    memcpy(&(addr->sin_addr), host->h_addr, host->h_length);

    // Step (3): Set the port value.
    addr->sin_port = htons(port);
    return 0;
}

int get_port_number(int sockfd) {
    struct sockaddr_in addr;
    socklen_t length = sizeof(addr);
    if (getsockname(sockfd, (sockaddr *)&addr, &length) == -1) {
        perror("Error getting port of socket");
        return -1;
    }
    return ntohs(addr.sin_port);
}

int send_data(int sockfd, std::string_view bytes) {
    size_t sent = 0;
    do {
        const ssize_t n =
            send(sockfd, bytes.data() + sent, bytes.size() - sent, 0);
        if (n < 0) {
            return -1;
        }
        sent += n;
    } while (sent < bytes.size());
    return 0;
}
