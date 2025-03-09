#ifndef TILESET_H
#define TILESET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* load_texture(const char* path, SDL_Renderer* renderer);

#endif
