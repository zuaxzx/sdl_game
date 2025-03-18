#ifndef LAYER_H
#define LAYER_H

#include <SDL2/SDL_image.h>

typedef struct
{
  int** maps;
  int length;
  int index;
  float delay; // seconds for switch
  float cycle; // seconds since last switch
  SDL_Texture* texture;
} texture_layer_t;

#endif
