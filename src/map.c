#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/config.h"
#include "../include/layer.h"
#include "../include/error.h"

int register_map(const char* filename, layer_t* layer)
{
  int* map = malloc(sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
  if (!map)
  {
    raise_error("Failed to allocate memory for the map.");
  }

  FILE* file = fopen(filename, "r");
  if (!file)
  {
    raise_error("No such file or directory.");
  }

  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      if (fscanf(file, "%d", &map[y * MAP_WIDTH + x]) != 1)
      {
        printf("Error: Invalid map format at row %d, col %d\n", y, x);
        free(map);
        fclose(file);
        return 0;
      }
    }
  }

  fclose(file);

  layer->maps = realloc(layer->maps, sizeof(int*) * (layer->length + 1));

  if (!layer->maps)
  {
    free(map);
    raise_error("Failed to allocate memory for layer->maps.");
  }

  layer->maps[layer->length] = map;
  layer->length++;
  return 1;
}

// TODO: Add renderer and tileset...
void render_map(int* map, SDL_Renderer* renderer, SDL_Texture* tileset)
{
  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      int tileID = map[y * MAP_WIDTH + x]; // Tile-ID aus der Map holen

      SDL_Rect src_rect = {tileID * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
      SDL_Rect dst_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

      SDL_RenderCopy(renderer, tileset, &src_rect, &dst_rect);
    }
  }
}
