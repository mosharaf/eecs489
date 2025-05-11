#pragma once

#include <cstdint>

enum class UpdateType : uint8_t {
  PLAYER_UPDATE = 0,
  GAME_UPDATE = 1,
};

struct Position {
  int x;
  int y;
};

struct PlayerUpdate {
  int id;
  Position position;
  int health;
};

struct GameUpdate {
  int id;
  int time_left;
};