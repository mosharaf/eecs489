#ifndef __DNS_Record_H__
#define __DNS_Record_H__

#include <cstring>
#include <sstream>

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


    /**
     * Encode DNSRecord before sending
     * @param header    DNSRecord to encode
     * @return          Encoded string
     */
    static std::string encode(const DNSRecord &record)
    {
        /*
         * WARNING: DON'T CHANGE THIS FUNCTION!
         */

        std::ostringstream oss;

        oss << record.TYPE << ' ' << record.CLASS << ' ' << record.TTL << ' ' << record.RDLENGTH << ':';

        std::string s1(record.NAME, 100);
        std::string s2(record.RDATA, 100);

        return oss.str() + s1 + s2;
    }


    /**
     * Decode DNSRecord from std::string
     * @param msgBuf            The received string to decode
     * @return DNSRecord        Decoded DNSRecord
     */
    static DNSRecord decode(const std::string &msgBuf)
    {
        /*
         * WARNING: DON'T CHANGE THIS FUNCTION!
         */

        DNSRecord record;

        int index = msgBuf.find(':');
        memcpy(record.NAME, msgBuf.data() + index + 1, 100);
        memcpy(record.RDATA, msgBuf.data() + index + 101, 100);

        std::istringstream iss(msgBuf);

        iss >> record.TYPE >> record.CLASS >> record.TTL >> record.RDLENGTH;

        return record;
    }
};

#endif