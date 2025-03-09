#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/tileset.h"

SDL_Texture* load_texture(const char* path, SDL_Renderer* renderer)
{
  SDL_Surface* surface = IMG_Load(path);
  if (!surface)
  {
    printf("surface\n");
    exit(1);
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}
