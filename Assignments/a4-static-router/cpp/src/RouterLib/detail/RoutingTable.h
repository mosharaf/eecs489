#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H
#include "RouterTypes.h"

#include <string>
#include <filesystem>
#include <unordered_map>

#include "IRoutingTable.h"

class RoutingTable : public IRoutingTable {
public:
    /**
     * @brief Constructs a RoutingTable object from a given file path.
     * @param routingTablePath The path to the file containing routing table entries.
     */
    explicit RoutingTable(const std::filesystem::path& routingTablePath);

    std::optional<RoutingEntry> getRoutingEntry(ip_addr ip) override;

    RoutingInterface getRoutingInterface(const std::string& iface) override;

    void setRoutingInterface(const std::string& iface, const mac_addr& mac, const ip_addr& ip) override;

    const std::unordered_map<std::string, RoutingInterface>& getRoutingInterfaces() const override;

private:
    std::vector<RoutingEntry> routingEntries; /**< Collection of routing entries. */
    std::unordered_map<std::string, RoutingInterface> routingInterfaces; /**< Map of interface names to routing interfaces. */
};



#endif //ROUTINGTABLE_H
