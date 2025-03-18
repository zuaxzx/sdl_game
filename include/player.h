#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "collision.h"
#include "layer.h"

// Static entity


// Entity
typedef struct
{
  SDL_Rect rect;
  float vx, vy;
  float target_speed;
  float speed;
  bool on_ground;
  collision_map_t collision;
} entity_t;

void check_and_push_model(entity_t* a, SDL_Rect b);
void update_player(entity_t* player, double delta_time);

#endif
