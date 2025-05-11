#include "BridgeClient.h"

#include <chrono>
#include <spdlog/spdlog.h>
#include <iostream>

#include "BridgeSender.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

// Constructor
BridgeClient::BridgeClient(std::filesystem::path routingTablePath,
                           std::string pcapPrefix)
    : dumper(pcapPrefix + "_input.pcap"), running(false) {
    routingTable = RoutingTableFactory::createRoutingTable(routingTablePath);

    // Set up the WebSocket connection
    try {
        // Look up the domain name
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve("localhost", "8080");

        // Make the connection on the IP address we get from a lookup
        tcp::socket socket(ioc);
        net::connect(socket, results);

        // Create the WebSocket stream
        ws = std::make_shared<WebSocketStream>(std::move(socket));

        // Set suggested timeout settings for the websocket
        ws->set_option(websocket::stream_base::timeout::suggested(
            beast::role_type::client)
        );

        ws->binary(true);

        // Perform the WebSocket handshake
        ws->handshake("localhost:8080", "/");

        // Create the BridgeSender
        bridgeSender = std::make_shared<BridgeSender>(ws, pcapPrefix);
        
        staticRouter = StaticRouterFactory::createRouter(
            routingTable, 
            bridgeSender, 
            std::chrono::seconds(15), 
            std::chrono::milliseconds(500),
            std::chrono::seconds(1)
        );

        spdlog::info("Connected to WebSocket server at ws://localhost:8080");
    } catch (const std::exception& e) {
        spdlog::error("Connection failed (is POX running?): {}", e.what());
        throw std::runtime_error("Could not create connection");
    }
}

BridgeClient::~BridgeClient() {
    if (running) {
        // Close the WebSocket connection
        spdlog::info("Closing WebSocket connection");
        boost::system::error_code ec;
        ws->close(websocket::close_code::normal, ec);
        if (ec)
            spdlog::error("Error closing WebSocket: {}", ec.message());
    }
}

// Method to request interfaces
void BridgeClient::setInterfaces(
    const router_bridge::InterfaceUpdate& interfaces) {
    for (const auto& iface : interfaces.interfaces()) {
        mac_addr mac;
        std::copy(iface.mac().begin(), iface.mac().begin() + mac.size(),
                  mac.begin());
        routingTable->setRoutingInterface(iface.name(), mac, iface.ip());
    }

    spdlog::info("Set interfaces, router ready to route things!");
}

void BridgeClient::onMessage(const std::string& message) {
    router_bridge::ProtocolMessage protoMessage;
    protoMessage.ParseFromString(message);

    if (protoMessage.has_router_packet()) {
        auto& packetMessage = protoMessage.router_packet();
        std::vector<uint8_t> packet(packetMessage.data().begin(),
                                    packetMessage.data().end());
        dumper.dump(packet);

        staticRouter->handlePacket(packet, packetMessage.interface());
    } else if (protoMessage.has_interface_update()) {
        setInterfaces(protoMessage.interface_update());
    }
}

void BridgeClient::doRead() {
    // Read a message into our buffer
    ws->async_read(
        buffer,
        [this](boost::system::error_code ec, std::size_t bytesTransferred) {
            onRead(ec, bytesTransferred);
        });
}

void BridgeClient::onRead(boost::system::error_code ec, std::size_t bytesTransferred) {
    if (ec) {
        if (ec == websocket::error::closed) {
            spdlog::info("WebSocket connection closed: {}", ec.message());
        } else {
            spdlog::error("WebSocket read error: {}", ec.message());
        }
        return;
    }

    // Process the message
    std::string message = beast::buffers_to_string(buffer.data());
    buffer.consume(buffer.size());  // Clear the buffer
    
    onMessage(message);

    // Queue up another read
    doRead();
}

void BridgeClient::run() {
    running = true;
    
    // Start the read loop
    doRead();
    
    // Run the Boost ASIO io_context
    ioc.run();
    
    running = false;
}