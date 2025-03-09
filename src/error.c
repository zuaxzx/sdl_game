#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

#include "../include/error.h"

void raise_error(const char* msg)
{
  printf("%s\n", msg);
  SDL_Quit();
  exit(1);
}
