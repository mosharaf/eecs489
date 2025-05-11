#include "BridgeSender.h"
#include <boost/system/error_code.hpp>
#include <spdlog/spdlog.h>

BridgeSender::BridgeSender(std::shared_ptr<WebSocketStream> ws,
                           std::string pcapPrefix)
    : ws(std::move(ws)), dumper(pcapPrefix + "_output.pcap") {}

void BridgeSender::sendPacket(Packet packet, const std::string& iface) {
    router_bridge::ProtocolMessage message;
    auto* routerPacket = message.mutable_router_packet();

    routerPacket->set_interface(iface);
    routerPacket->set_data(packet.data(), packet.size());

    dumper.dump(packet);
    send(message);
}

void BridgeSender::send(const router_bridge::ProtocolMessage& message) {
    std::string serialized = message.SerializeAsString();
    
    boost::system::error_code ec;
    ws->write(boost::asio::buffer(serialized), ec);
    
    if (ec) {
        spdlog::error("Error sending WebSocket message: {}", ec.message());
    }
}