#ifndef ROUTERTYPES_H
#define ROUTERTYPES_H

#include <chrono>
#include <vector>
#include <array>

constexpr inline uint8_t INIT_TTL = 255;

using mac_addr = std::array<uint8_t, 6>;
using ip_addr = uint32_t;
using Packet = std::vector<uint8_t>;

#endif //ROUTERTYPES_H
