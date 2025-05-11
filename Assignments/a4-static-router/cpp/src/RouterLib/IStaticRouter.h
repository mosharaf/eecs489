#ifndef ISTATICROUTER_H
#define ISTATICROUTER_H

#include <vector>
#include <string>

class IStaticRouter {
public:
    /**
     * @brief Handles an incoming packet, telling the switch to send out the necessary packets.
     * @param packet The incoming packet.
     * @param iface The interface on which the packet was received.
     */
    virtual void handlePacket(std::vector<uint8_t> packet, std::string iface) = 0;
    virtual ~IStaticRouter() = default;
};

#endif // ISTATICROUTER_H
