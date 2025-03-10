#include "../include/player.h"

void update_player(player_t* player, double delta_time)
{
  player->rect.y = player->rect.y + player->vy * delta_time;
  player->vy     = player->vy + 1 * delta_time;

  float diff = player->target_speed - player->speed;
  printf("Target: %f\n", player->target_speed);

  if (!player->target_speed)
  {
    player->speed = 0;
    return;
  }

  if (diff > delta_time)
  {
    player->speed += delta_time * 0.1;
  }
  else if (diff < delta_time)
  {
    player->speed -= delta_time * 0.1;
  }
  else
  {
    player->speed = player->target_speed;
  }
  player->rect.x += player->speed;
}


// Function to push the player out of a collision
void check_and_push_model(player_t* a, SDL_Rect b)
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
