#ifndef PACKETSENDER_H
#define PACKETSENDER_H

#include "RouterTypes.h"

class IPacketSender {
public:
    virtual ~IPacketSender() = default;

    /**
     * @brief Tells the switch to send the given packet on the given interface
     * @param packet The packet to send
     * @param iface The interface on which to send the packet
     */
    virtual void sendPacket(Packet packet, const std::string& iface) = 0;
};

#endif //PACKETSENDER_H
