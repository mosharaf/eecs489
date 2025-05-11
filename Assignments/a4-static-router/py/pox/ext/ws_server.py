import threading
import websockets
import asyncio

import router_bridge_pb2

from loguru import logger

class WSServer:
    def __init__(self, message_handler, host='localhost', port=8080):
        self.message_handler = message_handler
        self.host = host
        self.port = port
        
        self.server_thread = None
        self.loop = None
        self.client = None

        self.interface_message = None

    async def websocket_handler(self, websocket, path):
        logger.info("Client connected")
        self.client = websocket
        if self.interface_message is not None:
            logger.info("Sending interface message")
            await websocket.send(self.interface_message)
            logger.info("Interface message sent")
        else:
            logger.error("No interface message available")

        try:
            while True:
                message = await websocket.recv()
                if message:
                    self.message_handler(message)
                    
        except websockets.exceptions.ConnectionClosed:
            logger.info("Client disconnected")
            self.client = None

    async def _send_message(self, message):
        if self.client is not None:
            await self.client.send(message)
        else:
            logger.error("No client connected")

    def start_server(self):
        self.loop = asyncio.new_event_loop()
        asyncio.set_event_loop(self.loop)
        server = websockets.serve(self.websocket_handler, self.host, self.port)
        self.loop.run_until_complete(server)
        logger.info(f"WebSocket server running on ws://{self.host}:{self.port}")
        self.loop.run_forever()

    def send_message(self, message):
        self.loop.call_soon_threadsafe(self.loop.create_task, self._send_message(message))

    def start(self):
        if self.server_thread is None:
            self.server_thread = threading.Thread(target=self.start_server)
            self.server_thread.start()

    def stop(self):
        if self.loop is not None:
            self.loop.call_soon_threadsafe(self.loop.stop)
        if self.server_thread is not None:
            self.server_thread.join()
            self.server_thread = None
        logger.info("WebSocket server stopped")