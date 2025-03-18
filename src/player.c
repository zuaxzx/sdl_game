#include "../include/player.h"

void update_player(entity_t* player, double delta_time)
{
  player->rect.y = player->rect.y + player->vy * (float)delta_time / 80;
  player->vy     = player->vy + 1 * (float)delta_time / 80;

  printf("Target: %f\n", player->target_speed);
}


// Function to push the player out of a collision
void check_and_push_model(entity_t* a, SDL_Rect b)
{
  collision_map_t map = check_collision(a->rect, b);

  int overlap_left   = (a->rect.x + a->rect.w) - b.x;
  int overlap_right  = (b.x + b.w) - a->rect.x;
  int overlap_top    = (a->rect.y + a->rect.h) - b.y;
  int overlap_bottom = (b.y + b.h) - a->rect.y;

  /* Apply the correction only in the smallest overlapping direction */
  if (map.left)
  {
    a->rect.x -= overlap_left;
    a->vx = 0;
  }
  else if (map.right)
  {
    a->rect.x += overlap_right;
    a->vx = 0;
  }
  if (map.top)
  {
    a->rect.y -= overlap_top;
    a->vy        = 0;
    a->on_ground = true;
  }
  else if (map.bottom)
  {
    a->rect.y += overlap_bottom;
    a->vy        = 0;
    a->on_ground = true;
  }
}
