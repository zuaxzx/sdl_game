#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "SDL2/SDL.h"

typedef struct
{
  bool left;
  bool right;
  bool top;
  bool bottom;
} collision_map_t;

collision_map_t check_collision(SDL_Rect a, SDL_Rect b);

#endif
