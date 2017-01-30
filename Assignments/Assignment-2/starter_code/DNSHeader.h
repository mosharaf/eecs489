#ifndef __DNS_HEADER_H__
#define __DNS_HEADER_H__

struct DNSHeader
{
	ushort ID;
	bool QR;
	int OPCODE;
	bool AA;
	bool TC;
	bool RD;
	bool RA;
	char Z;
	char RCODE;
	ushort QDCOUNT;
	ushort ANCOUNT;
	ushort NSCOUNT;
	ushort ARCOUNT;
};

#endif