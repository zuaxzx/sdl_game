#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/game_loop.h"
#include "../include/config.h"
#include "../include/error.h"

SDL_Window* create_window(SDL_DisplayMode* dm)
{
  SDL_Window* window =
      SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm->w * 0.8,
                       dm->h * 0.8, SDL_WINDOW_SHOWN);
  if (window == NULL)
    raise_error("create_window");
  return window;
}

SDL_Renderer* register_renderer(SDL_Window* window)
{
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    raise_error("register_renderer");
  }
  return renderer;
}

int main(int argc, char* argv[])
{

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    raise_error("sdl_init");
  if (IMG_Init(IMG_INIT_PNG) < 0)
    raise_error("sdl_img_init");

  SDL_DisplayMode dm;
  if (SDL_GetCurrentDisplayMode(0, &dm) != 0)
    raise_error("sdl_dm");

  /* Create window and renderer */
  SDL_Window* window     = create_window(&dm);
  SDL_Renderer* renderer = register_renderer(window);

  game_loop(renderer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
