#ifndef PCAPDUMPER_H
#define PCAPDUMPER_H

#include <cstdint>
#include <fstream>
#include <vector>

struct PcapGlobalHeader {
    uint32_t magic_number;   // Magic number
    uint16_t version_major;  // Major version number
    uint16_t version_minor;  // Minor version number
    int32_t  thiszone;       // GMT to local correction
    uint32_t sigfigs;        // Accuracy of timestamps
    uint32_t snaplen;        // Max length of captured packets, in octets
    uint32_t network;        // Data link type

    PcapGlobalHeader() {
        magic_number = 0xa1b2c3d4;
        version_major = 2;
        version_minor = 4;
        thiszone = 0;
        sigfigs = 0;
        snaplen = 65535;
        network = 1; // DLT_EN10MB for Ethernet
    }
};

// PCAP Packet Record Header Structure
struct PcapPacketHeader {
    uint32_t ts_sec;   // Timestamp seconds
    uint32_t ts_usec;  // Timestamp microseconds
    uint32_t incl_len; // Number of bytes of packet saved in file
    uint32_t orig_len; // Actual length of packet

    PcapPacketHeader() : ts_sec(0), ts_usec(0), incl_len(0), orig_len(0) {}
};

class PcapDumper {
public:
    PcapDumper(const std::string &filename);
    ~PcapDumper();

    void dump(const std::vector<uint8_t> &data);

private:
    std::ofstream ofs;
    bool is_open;
};

#endif //PCAPDUMPER_H
