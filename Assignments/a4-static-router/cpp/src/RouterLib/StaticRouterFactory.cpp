#include "StaticRouterFactory.h"

#include "IRoutingTable.h"

#include "detail/StaticRouter.h"
#include "detail/ArpCache.h"

std::unique_ptr<IStaticRouter> StaticRouterFactory::createRouter(std::shared_ptr<IRoutingTable> routingTable,
                                                                 std::shared_ptr<IPacketSender> packetSender,
                                                                 std::chrono::milliseconds arpTimeout,
                                                                 std::chrono::milliseconds arpTickInterval,
                                                                 std::chrono::milliseconds arpResendInterval) {
    auto arpCache = std::make_unique<ArpCache>(arpTimeout, arpTickInterval, arpResendInterval, packetSender, routingTable);
    return std::make_unique<StaticRouter>(std::move(arpCache), routingTable, packetSender);
}
