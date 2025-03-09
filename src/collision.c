#include "SDL2/SDL.h"
#include "../include/collision.h"
#include "../include/player.h"

/* Return map of intersection */
collision_map_t check_collision(SDL_Rect a, SDL_Rect b)
{
  collision_map_t map = {false, false, false, false};

  if (SDL_HasIntersection(&a, &b))
  {
    int overlap_left   = (a.x + a.w) - b.x;
    int overlap_right  = (b.x + b.w) - a.x;
    int overlap_top    = (a.y + a.h) - b.y;
    int overlap_bottom = (b.y + b.h) - a.y;

    // Find the smallest overlap axis to determine the main push direction
    int min_horizontal = (overlap_left < overlap_right) ? overlap_left : overlap_right;
    int min_vertical   = (overlap_top < overlap_bottom) ? overlap_top : overlap_bottom;

    if (min_horizontal < min_vertical)
    {
      if (overlap_left < overlap_right)
      {
        map.left = true;
      }
      else
      {
        map.right = true;
      }
    }
    else
    {
      if (overlap_top < overlap_bottom)
      {
        map.top = true;
      }
      else
      {
        map.bottom = true;
      }
    }
  }

  return map;
}
