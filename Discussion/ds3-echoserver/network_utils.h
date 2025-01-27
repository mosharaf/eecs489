#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <arpa/inet.h>  // htons(), ntohs()
#include <netdb.h>      // gethostbyname(), struct hostent
#include <netinet/in.h> // struct sockaddr_in
#include <string_view>

const unsigned int MAX_MESSAGE_SIZE = 255; 
const unsigned int MAX_CLIENTS = 16; // Maximum number of clients that can connect
const unsigned int DEFAULT_SERVER_PORT = 8888; // Port number to listen on

/**
 * Make a server sockaddr given a port.
 *
 * Parameters:
 *   addr:  The sockaddr to modify (this is a C-style function).
 *   port:  The port on which to listen for incoming connections.
 *
 * Returns:
 *   0 on success, -1 on failure.
 */
int make_server_sockaddr(struct sockaddr_in *addr, int port);

/**
 * Make a client sockaddr given a remote hostname and port.
 *
 * Parameters:
 *   addr:      The sockaddr to modify (this is a C-style function).
 *   hostname:  Hostname of the remote host to connect to (like "141.88.27.42").
 *   port:      The port to use to connect to the remote hostname.
 *
 * Returns:
 *   0 on success, -1 on failure.
 */
int make_client_sockaddr(struct sockaddr_in *addr, const char *hostname,
                         int port);

/**
 * Return the port number assigned to a socket.
 *
 * Parameters:
 *   sockfd:  File descriptor of a socket.
 *
 * Returns:
 *   The port number of the socket, or -1 on failure.
 */
int get_port_number(int sockfd);

/**
 * Send a sequence of bytes over a TCP socket.
 *
 * Parameters:
 *   sockfd:  File descriptor of a socket.
 *   bytes:   The bytes to send.
 *
 * Returns:
 *   The size of the sequence if sending works; otherwise, return -1.
 */
int send_data(int sockfd, std::string_view bytes);

/** 
 * Receive a message of at most MAX_MESSAGE_SIZE + 1 bytes from a socket sockfd. 
 * Will continue receiving byte-by-byte until a newline is received
 */
int recv_data_until_newline(int sockfd, char *buffer);

#endif // NETWORK_UTILS_H
