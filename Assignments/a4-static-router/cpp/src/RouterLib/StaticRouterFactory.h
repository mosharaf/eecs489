#ifndef STATICROUTERFACTORY_H
#define STATICROUTERFACTORY_H
#include <chrono>
#include <filesystem>
#include <memory>

#include "IStaticRouter.h"
#include "IPacketSender.h"
#include "IRoutingTable.h"

class StaticRouterFactory {
public:
  static std::unique_ptr<IStaticRouter> createRouter(std::shared_ptr<IRoutingTable> routingTable,
                                                      std::shared_ptr<IPacketSender> packetSender,
                                                      std::chrono::milliseconds arpTimeout,
                                                      std::chrono::milliseconds arpTickInterval,
                                                      std::chrono::milliseconds arpResendInterval);
};


#endif //STATICROUTERFACTORY_H
