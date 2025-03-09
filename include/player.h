#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "collision.h"

typedef struct
{
  SDL_Rect rect; // Collision
  float vx, vy;  // Velocity
  float target_speed;
  float speed;
  bool on_ground;            // touching ground
  collision_map_t collision; // collision map
} player_t;

void check_and_push_model(player_t* a, SDL_Rect b);
void update_player(player_t* player, double delta_time);

#endif
