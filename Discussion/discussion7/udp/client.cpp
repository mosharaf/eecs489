#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#include "util.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "Error: usage is ./client <port_num>" << std::endl;
		return 1;
	}
	int portNum = atoi(argv[1]);

	// Note the SOCK_DGRAM and IPPROTO_UDP here
	int sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd < 1)
	{
		std::cout << "Couldn't create a socket\n";
		return 1;
	}

	// Set up a connection to the server -- same as before
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons((u_short) portNum);
	struct hostent* sp = gethostbyname("localhost");
	memcpy(&server.sin_addr, sp->h_addr, sp->h_length);
	int err = connect(sd, (sockaddr*) &server, sizeof(server));
	if(err == -1)
	{
		std::cout << "Error on connect\n";
		return 1;
	}

	char bump = 'a';
	// Notice I can still use send() because of connect()
	int bytesSent = send(sd, &bump, sizeof(bump), 0);
	if(bytesSent <= 0)
	{
		std::cout << "Error using send" << std::endl;
	}


	A a;
	B b;
	std::cout << "a value: " << a.val << " b value: " << b.val << std::endl;
	
	// recvfrom() setup
	iovec iov[2];
	iov[0].iov_base = &a;
	iov[0].iov_len = sizeof(a);
	iov[1].iov_base = &b;
	iov[1].iov_len = sizeof(b);
	msghdr msg;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_name = &server;
	msg.msg_namelen = sizeof(server);
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;

	int bytesRecvd = recvmsg(sd, &msg, 0);
	if(bytesRecvd <= 0)
	{
		std::cout << "Error on recvmsg" << std::endl;
		return 1;
	}
	std::cout << "a value: " << a.val << " b value: " << b.val << std::endl;

	return 0;
}