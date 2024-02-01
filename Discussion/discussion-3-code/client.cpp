#include <arpa/inet.h>		// ntohs()
#include <stdio.h>		// printf(), perror()
#include <stdlib.h>		// atoi()
#include <string.h>		// strlen()
#include <sys/socket.h>		// socket(), connect(), send(), recv()
#include <unistd.h>		// close()

#include "helpers.h"		// make_client_sockaddr()

static const int MAX_MESSAGE_SIZE = 256;

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
int send_message(const char *hostname, int port, const char *message) {
	if (strlen(message) > MAX_MESSAGE_SIZE) {
		perror("Error: Message exceeds maximum length\n");
		return -1;
	}

	// (1) Create a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// (2) Create a sockaddr_in to specify remote host and port
	struct sockaddr_in addr;
	if (make_client_sockaddr(&addr, hostname, port) == -1) {
		return -1;
	}

	// (3) Connect to remote server
	if (connect(sockfd, (sockaddr *) &addr, sizeof(addr)) == -1) {
		perror("Error connecting stream socket");
		return -1;
	}

	// (4) Receive greeting message from remote server
	char greeting_msg[256];
	ssize_t rval = recv(sockfd, greeting_msg, MAX_MESSAGE_SIZE, 0);
	printf("Receive greeting message: %s", greeting_msg);

	// (5) Send message to remote server
	size_t message_len = strlen(message);
	ssize_t n = send(sockfd, message, message_len, 0);

	// (6) Receive echo message from remote server
	char echo_message[256];
	ssize_t rval1 = recv(sockfd, echo_message, MAX_MESSAGE_SIZE, 0);
	printf("Receive echo message: %s\n", echo_message);

	// (5) Close connection
	close(sockfd);

	return 0;
}

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 4) {
		printf("Usage: ./client hostname port_num message\n");
		return 1;
	}
	const char *hostname = argv[1];
	int port = atoi(argv[2]);
	const char *message = argv[3];

	printf("Sending message %s to %s:%d\n", message, hostname, port);
	if (send_message(hostname, port, message) == -1) {
		return 1;
	}

	return 0;
}