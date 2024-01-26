#ifndef __DNS_Question_H__
#define __DNS_Question_H__

#include <cstring>
#include <sstream>

struct DNSQuestion
{
	char QNAME[100];
	ushort QTYPE;
	ushort QCLASS;

	DNSQuestion()
	{
		memset(QNAME, '\0', 100);
	}


	/**
	 * Encode DNSQuestion before sending
	 * @param question      DNSQuestion to encode
	 * @return              Encoded string
	 */
    static std::string encode(const DNSQuestion &question)
    {
        /*
         * WARNING: DON'T CHANGE THIS FUNCTION!
         */

        std::ostringstream oss;

        oss << question.QTYPE << ' ' << question.QCLASS << ':';

        std::string s1(question.QNAME, 100);

        return oss.str() + s1;
    }


    /**
     * Decode DNSQuestion from std::string
     * @param msgBuf        The received string to decode
     * @return              Decoded DNSQuestion
     */
    static DNSQuestion decode(const std::string &msgBuf)
    {
        /*
         * WARNING: DON'T CHANGE THIS FUNCTION!
         */

        DNSQuestion question;

        int index = msgBuf.find(':');
        memcpy(question.QNAME, msgBuf.data() + index + 1, 100);

        std::istringstream iss(msgBuf);

        iss >> question.QTYPE >> question.QCLASS;

        return question;
    }
};

#endif