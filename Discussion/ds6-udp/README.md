# EECS 489 Discussion 6 Exercise

## Overview

This assignment focuses on implementing UDP (User Datagram Protocol) functionality to exchange packets between a game server and client. You'll be working with a simple game communication system where the server sends player updates and game updates to clients, and clients receive and process these updates.

## Project Structure

```
ds6-udp/
├── CMakeLists.txt          # Main build configuration
├── src/                    # Source code directory
│   ├── client/             # Client implementation
│   │   ├── GameClient.cpp  # Client implementation (contains TODOs)
│   │   └── GameClient.h    # Client interface
│   ├── server/             # Server implementation
│   │   ├── GameServer.cpp  # Server implementation (contains TODOs)
│   │   └── GameServer.h    # Server interface
│   └── common/             # Shared code
│       ├── common.cpp      # Common utility functions implementation (contains TODOs)
│       ├── common.h        # Common utility functions declarations
│       └── GameTypes.h     # Game data structures
└── test/                   # Test directory
```

## Assignment Tasks

Based on the code examination, you need to implement the following TODOs:

1. **UDP Common Functions Implementation**
    - Complete the `create_udp_receiver` and `send_udp_packet` functions in common.cpp to provide an abstraction on sending and receiving UDP data.

1. **Client Implementation**:
   - Complete the client loop in `GameClient::start()` to receive and process UDP packets
   - Parse incoming packets to determine if they are player updates or game updates
   - Call the appropriate callback functions for each update type

1. **Server Implementation**:
   - Implement the `send_game_update()` function in `GameServer.cpp`
   - This function should create and send a game update packet to a client at the specified IP and port

## Data Structures

The assignment uses the following data structures defined in `GameTypes.h`:

- **UpdateType**: An enum class that identifies the type of update (PLAYER_UPDATE or GAME_UPDATE)
- **Position**: A struct containing x and y coordinates
- **PlayerUpdate**: A struct containing player ID, position, and health
- **GameUpdate**: A struct containing player ID and time left in the game

## Building the Project

To build the project:

```bash
# Create a build directory
mkdir -p build && cd build

# Configure the build
cmake ..

# Build the project
make
```

## Running the Tests

After building the project, you can run the tests to verify your implementation:

```bash
# From the build directory
./bin/GameServerTest
```