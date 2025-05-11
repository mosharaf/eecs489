#pragma once

#include <cstdint>

struct PacketHeader {
    uint32_t type;     // 0: START; 1: END; 2: DATA; 3: ACK
    uint32_t seqNum;   // Described below
    uint32_t length;   // Length of data; 0 for ACK packets
    uint32_t checksum; // 32-bit CRC
};
