#include "PCAPDumper.h"

#include <chrono>
#include <stdexcept>
#include <spdlog/spdlog.h>


PcapDumper::PcapDumper(const std::string &filename) : is_open(false) {
    ofs.open(filename, std::ios::out | std::ios::binary);
    if (!ofs.is_open()) {
        spdlog::error("Failed to open file: {}", filename);
        return;
    }

    PcapGlobalHeader global_header;
    ofs.write(reinterpret_cast<const char*>(&global_header), sizeof(global_header));
    if (!ofs) {
        spdlog::error("Failed to write global header to file: {}", filename);
        ofs.close();
        return;
    }

    is_open = true;
}

PcapDumper::~PcapDumper() {
    if (ofs.is_open()) {
        ofs.close();
    }
}

void PcapDumper::dump(const std::vector<uint8_t> &data) {
    if (!is_open) {
        spdlog::error("File is not open for writing.");
        return;
    }

    PcapPacketHeader pkt_header;

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000000;

    pkt_header.ts_sec = static_cast<uint32_t>(seconds);
    pkt_header.ts_usec = static_cast<uint32_t>(microseconds);
    pkt_header.incl_len = static_cast<uint32_t>(data.size());
    pkt_header.orig_len = static_cast<uint32_t>(data.size());

    ofs.write(reinterpret_cast<const char*>(&pkt_header), sizeof(pkt_header));
    if (!ofs) {
        spdlog::error("Failed to write packet header.");
        return;
    }

    if (!data.empty()) {
        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
        if (!ofs) {
            spdlog::error("Failed to write packet data.");
            return;
        }
        ofs.flush();
    }
}
