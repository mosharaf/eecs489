#ifndef __DNS_Record_H__
#define __DNS_Record_H__

#include <string.h>

struct DNSRecord
{
	char NAME[100];
	ushort TYPE;
	ushort CLASS;
	ushort TTL;
	ushort RDLENGTH;
	char RDATA[100];

	DNSRecord()
	{
		memset(NAME, '\0', 100);
		memset(RDATA, '\0', 100);
	}
};

#endif