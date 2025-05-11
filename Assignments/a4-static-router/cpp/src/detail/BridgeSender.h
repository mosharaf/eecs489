#ifndef BRIDGESENDER_H
#define BRIDGESENDER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <memory>
#include <string>

#include "IPacketSender.h"
#include "PCAPDumper.h"
#include "router_bridge.pb.h"

class BridgeSender : public IPacketSender {
   public:
    using WebSocketStream = boost::beast::websocket::stream<boost::asio::ip::tcp::socket>;

    BridgeSender(std::shared_ptr<WebSocketStream> ws, std::string pcapPrefix);

    void sendPacket(Packet packet, const std::string& iface) override;

   private:
    void send(const router_bridge::ProtocolMessage& message);

    std::shared_ptr<WebSocketStream> ws;
    PcapDumper dumper;
};

#endif  // BRIDGESENDER_H