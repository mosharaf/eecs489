#ifndef ROUTINGTABLEFACTORY_H
#define ROUTINGTABLEFACTORY_H

#include <filesystem>
#include <memory>

#include "IRoutingTable.h"

class RoutingTableFactory {
public:
  static std::unique_ptr<IRoutingTable> createRoutingTable(std::filesystem::path routingTablePath);
};


#endif //ROUTINGTABLEFACTORY_H
