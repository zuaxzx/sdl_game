#include <SDL2/SDL.h>
#include "../include/game_loop.h"
#include "../include/player.h"
#include "../include/layer.h"
#include "../include/tileset.h"
#include "../include/map.h"
#include "../include/error.h"

#include <stdint.h>




void game_loop(SDL_Renderer* renderer)
{
  uint32_t delta_time = 0;
  int quit                    = 0;
  int keys[SDL_NUM_SCANCODES] = {0};
  SDL_Event event;
  uint32_t current_time = 0;
  uint32_t last_time    = SDL_GetTicks();


  /* Tilesets */

  SDL_Texture* tileset = load_texture("test.png", renderer);
  if (!tileset)
  {
    raise_error("load test.png\n");
  }

  /* Texture */

  texture_layer_t default_layer = {NULL, 0, 0, 1.0f, 0.0f, tileset};

  /* Layers */

  if (!register_map("level.map", &default_layer))
  {
    raise_error("load level1.map\n");
  }
  //if (!register_map("level2.map", &default_layer))
  //{
  //  raise_error("load level2.map\n");
  //}

  /* Collision */

  entity_t player = {{0, 0, 32, 32}, 0.0f, 0.0f, 0.0f, 0.0f, true, {true, true, true, true}};

  while (!quit)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT)
      {
        quit = 1;
      }
      if (event.type == SDL_KEYDOWN)
      {
        keys[event.key.keysym.scancode] = 1;
      }
      else if (event.type == SDL_KEYUP)
      {
        keys[event.key.keysym.scancode] = 0;
      }
    }

    current_time = SDL_GetTicks();
    delta_time   = current_time - last_time;
    //if (delta_time > 0.15f)
    //  delta_time = 0.15f;

    if (keys[SDL_SCANCODE_SPACE] && player.on_ground)
    {
      player.on_ground = false;
      player.vy        = -20;
    }
    if (keys[SDL_SCANCODE_D])
    {
      player.rect.x += 2 * delta_time / 4;
    }
    if (keys[SDL_SCANCODE_A])
    {
      player.rect.x -= 2 * delta_time / 4;
    }
    update_player(&player, delta_time);

    SDL_RenderClear(renderer);
    if (default_layer.maps)
    		render_map(default_layer.maps[default_layer.index], renderer, default_layer.texture);

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(renderer, &player.rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /* Render on screen */
    SDL_RenderPresent(renderer);

    if (default_layer.delay <= default_layer.cycle)
    {
      default_layer.index++;
      default_layer.cycle = 0;
    }
    if (default_layer.index >= default_layer.length)
      default_layer.index = 0;

    default_layer.cycle += (float)delta_time / 1000;

    SDL_Delay(1);
    last_time = current_time;
    printf("%f", player.vy);
    printf("%d", player.rect.y);
  }

  for (int i = 0; i < default_layer.length; i++)
  {
    free(default_layer.maps[i]);
  }
  free(default_layer.maps);
  SDL_DestroyTexture(tileset);
}
