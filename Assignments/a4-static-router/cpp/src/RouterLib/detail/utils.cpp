#include "utils.h"

#include <spdlog/spdlog.h>

#include "protocol.h"

uint16_t cksum (const void *_data, int len) {
  const uint8_t *data = static_cast<const uint8_t*>(_data);
  uint32_t sum;

  for (sum = 0;len >= 2; data += 2, len -= 2)
    sum += data[0] << 8 | data[1];
  if (len > 0)
    sum += data[0] << 8;
  while (sum > 0xffff)
    sum = (sum >> 16) + (sum & 0xffff);
  sum = htons (~sum);
  return sum ? sum : 0xffff;
}

/* Converts a MAC address from void* to mac_addr */
mac_addr make_mac_addr(void* addr) {
  mac_addr mac;
  uint8_t* ptr = static_cast<uint8_t*>(addr);
  for (size_t i = 0; i < ETHER_ADDR_LEN; ++i) {
    mac[i] = ptr[i];
  }

  return mac;
}

uint16_t ethertype(uint8_t* buf) {
  sr_ethernet_hdr_t* ehdr = (sr_ethernet_hdr_t*)buf;
  return ntohs(ehdr->ether_type);
}

uint8_t ip_protocol(uint8_t* buf) {
  sr_ip_hdr_t* iphdr = (sr_ip_hdr_t*)(buf);
  return iphdr->ip_p;
}

/* Prints out formatted Ethernet address, e.g. 00:11:22:33:44:55 */
void print_addr_eth(uint8_t* addr) {
  int pos = 0;
  uint8_t cur;
  std::string eth_addr;
  for (; pos < ETHER_ADDR_LEN; pos++) {
    cur = addr[pos];
    if (pos > 0)
      eth_addr += ":";
    eth_addr += fmt::format("{:02X}", cur);
  }
  spdlog::info("{}", eth_addr);
}

/* Prints out IP address as a string from in_addr */
void print_addr_ip(struct in_addr address) {
  char buf[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &address, buf, sizeof(buf)) == NULL)
    spdlog::error("inet_ntop error on address conversion");
  else
    spdlog::info("{}", buf);
}

/* Prints out IP address from integer value */
void print_addr_ip_int(uint32_t ip) {
  spdlog::info("{}.{}.{}.{}", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

/* Prints out fields in Ethernet header. */
void print_hdr_eth(uint8_t* buf) {
  sr_ethernet_hdr_t* ehdr = (sr_ethernet_hdr_t*)buf;
  spdlog::info("ETHERNET header:");
  spdlog::info("\tdestination: ");
  print_addr_eth(ehdr->ether_dhost);
  spdlog::info("\tsource: ");
  print_addr_eth(ehdr->ether_shost);
  spdlog::info("\ttype: {}", ntohs(ehdr->ether_type));
}

/* Prints out fields in IP header. */
void print_hdr_ip(uint8_t* buf) {
  sr_ip_hdr_t* iphdr = (sr_ip_hdr_t*)(buf);
  spdlog::info("IP header:");
  spdlog::info("\tversion: {}", static_cast<int>(iphdr->ip_v));
  spdlog::info("\theader length: {}", static_cast<int>(iphdr->ip_hl));
  spdlog::info("\ttype of service: {}", iphdr->ip_tos);
  spdlog::info("\tlength: {}", ntohs(iphdr->ip_len));
  spdlog::info("\tid: {}", ntohs(iphdr->ip_id));

  if (ntohs(iphdr->ip_off) & IP_DF)
    spdlog::info("\tfragment flag: DF");
  else if (ntohs(iphdr->ip_off) & IP_MF)
    spdlog::info("\tfragment flag: MF");
  else if (ntohs(iphdr->ip_off) & IP_RF)
    spdlog::info("\tfragment flag: R");

  spdlog::info("\tfragment offset: {}", ntohs(iphdr->ip_off) & IP_OFFMASK);
  spdlog::info("\tTTL: {}", iphdr->ip_ttl);
  spdlog::info("\tprotocol: {}", iphdr->ip_p);
  spdlog::info("\tchecksum: {}", static_cast<uint32_t>(iphdr->ip_sum));
  spdlog::info("\tsource: ");
  print_addr_ip_int(ntohl(iphdr->ip_src));
  spdlog::info("\tdestination: ");
  print_addr_ip_int(ntohl(iphdr->ip_dst));
}

/* Prints out ICMP header fields */
void print_hdr_icmp(uint8_t* buf) {
  sr_icmp_hdr_t* icmp_hdr = (sr_icmp_hdr_t*)(buf);
  spdlog::info("ICMP header:");
  spdlog::info("\ttype: {}", icmp_hdr->icmp_type);
  spdlog::info("\tcode: {}", icmp_hdr->icmp_code);
  spdlog::info("\tchecksum: {}", static_cast<uint32_t>(icmp_hdr->icmp_sum));
}

/* Prints out fields in ARP header */
void print_hdr_arp(uint8_t* buf) {
  sr_arp_hdr_t* arp_hdr = (sr_arp_hdr_t*)(buf);
  spdlog::info("ARP header");
  spdlog::info("\thardware type: {}", ntohs(arp_hdr->ar_hrd));
  spdlog::info("\tprotocol type: {}", ntohs(arp_hdr->ar_pro));
  spdlog::info("\thardware address length: {}", arp_hdr->ar_hln);
  spdlog::info("\tprotocol address length: {}", arp_hdr->ar_pln);
  spdlog::info("\topcode: {}", ntohs(arp_hdr->ar_op));
  spdlog::info("\tsender hardware address: ");
  print_addr_eth(arp_hdr->ar_sha);
  spdlog::info("\tsender ip address: ");
  print_addr_ip_int(ntohl(arp_hdr->ar_sip));
  spdlog::info("\ttarget hardware address: ");
  print_addr_eth(arp_hdr->ar_tha);
  spdlog::info("\ttarget ip address: ");
  print_addr_ip_int(ntohl(arp_hdr->ar_tip));
}

/* Prints out all possible headers, starting from Ethernet */
void print_hdrs(uint8_t* buf, uint32_t length) {
  /* Ethernet */
  int minlength = sizeof(sr_ethernet_hdr_t);
  if (length < minlength) {
    spdlog::error("Failed to print ETHERNET header, insufficient length");
    return;
  }

  uint16_t ethtype = ethertype(buf);
  print_hdr_eth(buf);

  if (ethtype == ethertype_ip) {
    /* IP */
    minlength += sizeof(sr_ip_hdr_t);
    if (length < minlength) {
      spdlog::error("Failed to print IP header, insufficient length");
      return;
    }

    print_hdr_ip(buf + sizeof(sr_ethernet_hdr_t));
    uint8_t ip_proto = ip_protocol(buf + sizeof(sr_ethernet_hdr_t));

    if (ip_proto == ip_protocol_icmp) {
      /* ICMP */
      minlength += sizeof(sr_icmp_hdr_t);
      if (length < minlength)
        spdlog::error("Failed to print ICMP header, insufficient length");
      else
        print_hdr_icmp(buf + sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t));
    }
  }
  else if (ethtype == ethertype_arp) {
    /* ARP */
    minlength += sizeof(sr_arp_hdr_t);
    if (length < minlength)
      spdlog::error("Failed to print ARP header, insufficient length");
    else
      print_hdr_arp(buf + sizeof(sr_ethernet_hdr_t));
  }
  else {
    spdlog::error("Unrecognized Ethernet Type: {}", ethtype);
  }
}
