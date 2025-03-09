#include <SDL2/SDL.h>
#include "../include/game_loop.h"
#include "../include/player.h"
#include "../include/layer.h"
#include "../include/tileset.h"
#include "../include/map.h"


void game_loop(SDL_Renderer* renderer)
{
  double delta_time = 0.0;
  int quit                    = 0;
  int keys[SDL_NUM_SCANCODES] = {0};
  SDL_Event event;
  uint64_t current_time = SDL_GetPerformanceCounter();
  uint64_t last_time    = 0;

  SDL_Texture* tileset;
  tileset = load_texture("test.png", renderer);
  if (!tileset)
  {
    printf("tileset\n");
    exit(1);
  }

  player_t player = {{100, 100, 100, 100}, 0.0f, 0.0f, 0.0f, 0.0f, false, {true, true, true, true}};

  layer_t default_layer = {NULL, 0, 0, 1.0f, 0.0f};

  if (!register_map("level.map", &default_layer))
  {
    exit(1); // Exit if loading failed
  }
  if (!register_map("level2.map", &default_layer))
  {
    exit(1); // Exit if loading failed
  }

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
    if (delta_time > 0.15f)
      delta_time = 0.15f;

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    if (keys[SDL_SCANCODE_SPACE] && player.on_ground)
    {
      player.on_ground = false;
      player.vy        = -20;
    }
    // if (keys[SDL_SCANCODE_D] | keys[SDL_SCANCODE_A])
    //{
    //   double target_speed = 0;
    //   if (keys[SDL_SCANCODE_D])
    //   {
    //     target_speed += 2;
    //   }
    //   if (keys[SDL_SCANCODE_A])
    //   {
    //     target_speed += -2;
    //   }
    //   player.target_speed = target_speed;
    // }
    // else
    //{
    //   player.target_speed = 0;
    // }

    update_player(&player, delta_time);

    /* Render on screen */
    SDL_RenderPresent(renderer);

    if (default_layer.delay <= default_layer.cycle)
    {
      default_layer.index++;
      default_layer.cycle = 0;
    }
    if (default_layer.index >= default_layer.length)
      default_layer.index = 0;
    default_layer.cycle += delta_time;

    SDL_Delay(1);
    last_time = current_time;
  }

  for (int i = 0; i < default_layer.length; i++)
  {
    free(default_layer.maps[i]);
  }
  free(default_layer.maps);
  SDL_DestroyTexture(tileset);
}
