#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "Error: usage is ./server <port_num>" << std::endl;
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

	struct sockaddr_in self;
	memset((char *) &self, 0, sizeof(struct sockaddr_in));
	self.sin_family = AF_INET;
	self.sin_addr.s_addr = INADDR_ANY;
	self.sin_port = htons(portNum);

	int err = bind(sd, (struct sockaddr*) &self, sizeof(struct sockaddr_in));
	if(err == -1)
	{
		std::cout << "Error on binding\n";
		return 1;
	}

	// Note there is no more listen or accept -- what does this imply?
	const int BUF_LEN = 10000;
	char buf[BUF_LEN];
	memset(buf, '\0', BUF_LEN);
	// Use recvfrom() to extract IP address and port of sender
	// If you don't need these, you can use recv() instead
	// UDP packets have boundaries, recv() returns a message at a time, i.e. no need for a loop for recv()
	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	int bytesRecvd = recvfrom(sd, buf, BUF_LEN, 0, (sockaddr*) &clientAddr, &clientAddrSize);
	if(bytesRecvd <= 0)
	{
		std::cout << "Error receiving message over socket" << std::endl;
		return 1;
	}
	std::cout << "Got message from: " << inet_ntoa(clientAddr.sin_addr) << ':' << ntohs(clientAddr.sin_port) << std::endl;
	std::cout << "Got: " << buf << " bytes received: " << bytesRecvd << std::endl;

	// Can also send packets using sendto() (syntax is very similar to send())
	// or even send() if you tell the kernel to "remember" the address and port using connect()
	// Here I'll show how to use sendmsg() (an example of a scattered send)
	A a;
	B b;
	a.val = 123;
	b.val = 456;

	iovec iov[2];
	iov[0].iov_base = &a;
	iov[0].iov_len = sizeof(a);
	iov[1].iov_base = &b;
	iov[1].iov_len = sizeof(b);
	msghdr msg;
	msg.msg_name = &clientAddr;
	msg.msg_namelen = sizeof(clientAddr);
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;

	err = sendmsg(sd, &msg, 0);
	if(err <= 0)
	{
		std::cout << "Error using sendmsg" << std::endl;
	}

	return 0;
}