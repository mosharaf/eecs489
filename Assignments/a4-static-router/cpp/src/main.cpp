#include <iostream>

#include "detail/BridgeClient.h"
#include "detail/cxxopts.hpp"

int main(int argc, char **argv)
{
    cxxopts::Options options("StaticRouter", "Static Router for EECS 489 P4");
    options.add_options()
        ("h,help", "Print help")
        ("r,routing-table", "Path to routing table", cxxopts::value<std::string>()->default_value("rtable"))
        ("p,pcap-prefix", "Prefix for pcap files", cxxopts::value<std::string>()->default_value("sr_capture"));

    auto result = options.parse(argc, argv);

    BridgeClient client(result["routing-table"].as<std::string>(), result["pcap-prefix"].as<std::string>());
    client.run();
}