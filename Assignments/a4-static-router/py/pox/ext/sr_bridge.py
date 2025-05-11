from pox.core import core
import pox.openflow.libopenflow_01 as of

from ws_server import WSServer

from threading import Thread
from router_bridge_pb2 import ProtocolMessage, InterfaceUpdate, Interface, RouterPacket

from loguru import logger
import struct
import socket
import re

class SRBridge:
    def __init__(self):
        self.switch_connections = None
        self.ip_config = self.get_ip_config()
        self.port_to_interface = {}
        self.intf_to_port = {}

        self.ws_server = WSServer(self.send_packet_to_router)
        self.ws_server.start()

    def get_ip_config(self):
        # Read IP configuration from file
        ip_config = {}
        with open("IP_CONFIG", "r") as f:
            for line in f:
                parts = re.split(r'\s+', line.strip())
                if len(parts) != 2:
                    logger.error("Invalid IP configuration line: {}", line)
                    continue

                intf_name, ip_addr = parts
                if "-" not in intf_name:
                    continue

                intf_name = intf_name.split("-")[1]
                ip_addr = struct.unpack("<I", socket.inet_aton(parts[1].strip()))[0]
                ip_config[intf_name] = ip_addr

        return ip_config

    def _handle_ConnectionUp(self, event):
        logger.info("Switch {} has connected", event.dpid)
        self.switch_connection = event.connection

        interfaces = []

        # Print switch interface information
        for port in event.ofp.ports:
            split_name = port.name.split("-")
            if len(split_name) != 2:
                continue
            
            name = split_name[1]
            mac_addr = port.hw_addr.toRaw()
            mac_hex = port.hw_addr.toStr()
            ip_addr = self.ip_config[name]

            self.port_to_interface[port.port_no] = name
            self.intf_to_port[name] = port.port_no

            logger.info("Interface {} MAC {} IP {}", name, mac_hex, ip_addr)
            interfaces.append(Interface(name=name, mac=mac_addr, ip=ip_addr))

        msg = ProtocolMessage()
        msg.interface_update.interfaces.extend(interfaces)
        self.ws_server.interface_message = msg.SerializeToString()

    def _handle_PacketIn(self, event):
        logger.info("Packet in from switch {} on interface {}", event.dpid, self.port_to_interface[event.port])
        data = event.data

        logger.info("Data of length {} bytes received", len(data))

        # Send packet to router
        interface = self.port_to_interface[event.port]

        msg = ProtocolMessage()
        msg.router_packet.data = data
        msg.router_packet.interface = interface
        self.ws_server.send_message(msg.SerializeToString())


    def send_packet_to_router(self, data):

        # Deserialize message
        msg = ProtocolMessage()
        msg.ParseFromString(data)

        interface = msg.router_packet.interface
        data = msg.router_packet.data

        port = self.intf_to_port[interface]
        msg = of.ofp_packet_out()
        msg.data = data
        msg.in_port = of.OFPP_NONE
        msg.actions.append(of.ofp_action_output(port=port))

        logger.info("Sending data of length {} bytes out on interface {}", len(data), interface)
        self.switch_connection.send(msg)

# Launch function to start the module
def launch():
    # Register event listeners
    sr_bridge = SRBridge()
    core.openflow.addListenerByName("ConnectionUp", sr_bridge._handle_ConnectionUp)
    core.openflow.addListenerByName("PacketIn", sr_bridge._handle_PacketIn)

    logger.info("EECS 489 SR Bridge running.")
