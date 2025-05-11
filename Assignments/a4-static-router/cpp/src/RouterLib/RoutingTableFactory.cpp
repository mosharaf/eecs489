#include "RoutingTableFactory.h"

#include "IRoutingTable.h"

#include "detail/RoutingTable.h"

std::unique_ptr<IRoutingTable> RoutingTableFactory::createRoutingTable(std::filesystem::path routingTablePath) {
    return std::make_unique<RoutingTable>(routingTablePath);
}
