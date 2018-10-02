#ifndef __DNS_HEADER_H__
#define __DNS_HEADER_H__

#include <cstring>
#include <sstream>

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


	/**
	 * Encode DNSHeader before sending
	 * @param header    DNSHeader to encode
	 * @return          Encoded string
	 */
	static std::string encode(const DNSHeader &header)
	{
	    /*
	     * WARNING: DON'T CHANGE THIS FUNCTION!
	     */

	    std::ostringstream oss;

	    oss << header.ID << ' ' <<  header.QR << ' ' <<  header.OPCODE << ' ' <<  header.AA << ' ' << header.TC << ' '
	    <<  header.RD << ' ' <<  header.RA << ' ' <<  (int) header.Z << ' ' <<  (int) header.RCODE << ' ' <<  header.QDCOUNT << ' '
	    <<  header.ANCOUNT << ' ' <<  header.NSCOUNT << ' ' << header.ARCOUNT;

        return oss.str();
	}

	/**
	 * Decode DNSHeader from std::string
	 * @param msgBuf    The received string to decode
	 * @return          Decoded DNSHeader
	 */
	static DNSHeader decode(const std::string &msgBuf)
	{
        /*
         * WARNING: DON'T CHANGE THIS FUNCTION!
         */

        DNSHeader header;
        std::istringstream iss(msgBuf);

        int Z;
        int RCODE;

        iss >> header.ID >>  header.QR >>  header.OPCODE >>  header.AA >> header.TC >>  header.RD >>  header.RA >>
        Z >>  RCODE >>  header.QDCOUNT >>  header.ANCOUNT >>  header.NSCOUNT >> header.ARCOUNT;

        header.Z = Z;
        header.RCODE = RCODE;

        return header;
	}
};


#endif