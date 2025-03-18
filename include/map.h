#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "../include/layer.h"

int register_map(const char* filename, texture_layer_t* layer);
void render_map(int* map, SDL_Renderer* renderer, SDL_Texture* tileset);

#endif
