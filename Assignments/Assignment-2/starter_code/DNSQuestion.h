#ifndef __DNS_Question_H__
#define __DNS_Question_H__

#include <string.h>

struct DNSQuestion
{
	char QNAME[100];
	ushort QTYPE;
	ushort QCLASS;

	DNSQuestion()
	{
		memset(QNAME, '\0', 100);
	}
};

#endif