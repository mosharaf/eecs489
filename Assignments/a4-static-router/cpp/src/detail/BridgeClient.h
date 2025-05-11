#ifndef BRIDGECLIENT_H
#define BRIDGECLIENT_H

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <memory>
#include <string>
#include <filesystem>

#include "PCAPDumper.h"
#include "RoutingTableFactory.h"
#include "StaticRouterFactory.h"
#include "router_bridge.pb.h"

// Forward declarations
class BridgeSender;

class BridgeClient {
   public:
    using WebSocketStream = boost::beast::websocket::stream<boost::asio::ip::tcp::socket>;

    BridgeClient(std::filesystem::path routingTablePath,
                 std::string pcapPrefix);
    ~BridgeClient();

    void setInterfaces(const router_bridge::InterfaceUpdate& interfaces);

    void run();

   private:
    void onMessage(const std::string& message);
    void doRead();
    void onRead(boost::system::error_code ec, std::size_t bytesTransferred);

    // Boost Asio and Beast components
    boost::asio::io_context ioc;
    std::shared_ptr<WebSocketStream> ws;
    boost::beast::flat_buffer buffer;

    std::shared_ptr<IRoutingTable> routingTable;
    std::shared_ptr<BridgeSender> bridgeSender;
    std::unique_ptr<IStaticRouter> staticRouter;

    PcapDumper dumper;
    bool running;
};

#endif  // BRIDGECLIENT_H