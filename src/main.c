#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define WINDOW_TITLE "Test build"

const float GRAVITY = 0.8;
const float JUMP_STRENGTH = -3.0f;
const float MAX_JUMP_VELOCITY = -12.0f;
const float SPEED = 100.0f;
double delta_time;
float accel;

void raise_error(const char* msg)
{
  printf("%s\n", msg);
  SDL_Quit();
  exit(1);
}

SDL_Window* create_window()
{
  SDL_Window* window =
      SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                       SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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


// Struct for collision detection
typedef struct {
    bool left;
    bool right;
    bool top;
    bool bottom;
} collision_map_t;

/* Return map of intersection */
collision_map_t check_collision(SDL_Rect a, SDL_Rect b) {
    collision_map_t map = {false, false, false, false};

    if (SDL_HasIntersection(&a, &b)) {
        int overlap_left   = (a.x + a.w) - b.x;
        int overlap_right  = (b.x + b.w) - a.x;
        int overlap_top    = (a.y + a.h) - b.y;
        int overlap_bottom = (b.y + b.h) - a.y;

        // Find the smallest overlap axis to determine the main push direction
        int min_horizontal = (overlap_left < overlap_right) ? overlap_left : overlap_right;
        int min_vertical = (overlap_top < overlap_bottom) ? overlap_top : overlap_bottom;

        if (min_horizontal < min_vertical) {
            if (overlap_left < overlap_right) {
                map.left = true;
            } else {
                map.right = true;
            }
        } else {
            if (overlap_top < overlap_bottom) {
                map.top = true;
            } else {
                map.bottom = true;
            }
        }
    }

    return map;
}

typedef struct {
    SDL_Rect rect; // Collision
    float vx, vy;  // Velocity
    float target_speed;
    float speed;
    bool on_ground;  // touching ground
    collision_map_t collision; // collision map
} player_t;

// Function to push the player out of a collision
void check_and_push_model(player_t* a, SDL_Rect b) {
    collision_map_t map = check_collision(a->rect, b);

    int overlap_left   = (a->rect.x + a->rect.w) - b.x;
    int overlap_right  = (b.x + b.w) - a->rect.x;
    int overlap_top    = (a->rect.y + a->rect.h) - b.y;
    int overlap_bottom = (b.y + b.h) - a->rect.y;

    /* Apply the correction only in the smallest overlapping direction */
    if (map.left) {
        a->rect.x -= overlap_left;
        a->vx = 0;
    } else if (map.right) {
        a->rect.x += overlap_right;
        a->vx = 0;
    }
    if (map.top) {
        a->rect.y -= overlap_top;
        a->vy = 0;
        a->on_ground = true;
    } else if (map.bottom) {
        a->rect.y += overlap_bottom;
        a->vy = 0;
        a->on_ground = true;
    }
}


void update_player(player_t* player)
{

  //pos_y = pos_y + (velocity_y * time_difference) + (gravity_y * (time_difference ^ 2) / 2)
  //velocity_y = velocity_y + (acceleration_y * time_difference)
  //player->rect.y += (player->vy * delta_time) + (GRAVITY * ( pow(delta_time, 2)) / 2);
  //player->vy += player->vy + (accel * delta_time);
  player->rect.y = player->rect.y + player->vy * delta_time;
  player->vy = player->vy + 1 * delta_time;

  float diff = player->target_speed - player->speed;
  printf("Target: %f\n", player->target_speed);

  if (!player->target_speed) {
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

int main(int argc, char* argv[])
{

  /* Init SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    raise_error("sdl_init");
  }

  /* Create window and renderer */
  SDL_Window* window     = create_window();
  SDL_Renderer* renderer = register_renderer(window);

  player_t player = {{100, 100, 100, 100}, 0.0f, 0.0f, 0.0f, 0.0f, false, {true, true, true, true}};

  int keys[SDL_NUM_SCANCODES] = {0};

  SDL_Event event;
  uint64_t current_time = SDL_GetPerformanceCounter();
  uint64_t last_time = 0;
  delta_time = 0.0;
  accel = 1.0f;
  //int speed = 10;
  //float gravity = 9.8f;
  //float velocity = 0.0f;
  //bool jump = false;
  /* TODO: Replace with a timer */

  //int jump_strength = 15;
  int quit  = 0;
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
    delta_time = current_time - last_time;
    //current_time = SDL_GetPerformanceCounter();
    //delta_time = (double)((current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency() );
    if (delta_time > 0.15f)
      delta_time = 0.15f;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Schwarz
    SDL_RenderClear(renderer);

    // Zeichne ein rotes Rechteck
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);           // Rot
    SDL_Rect rect  = {0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50}; // Position und Größe des Rechtecks
    //SDL_Rect rect2 = {200, SCREEN_HEIGHT - 400, 100, 400};
    SDL_RenderFillRect(renderer, &rect);
    //SDL_RenderFillRect(renderer, &rect2);

    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    if (keys[SDL_SCANCODE_SPACE] && player.on_ground)
    {
      player.on_ground = false;
      player.vy = -20;
      //player.vy += JUMP_STRENGTH * delta_time;
      printf("JUMP\n");
    }
    if (keys[SDL_SCANCODE_D] | keys[SDL_SCANCODE_A])
    {
      double target_speed = 0;
      if (keys[SDL_SCANCODE_D])
      {
        printf("D");
        target_speed += 2;
      }
      if (keys[SDL_SCANCODE_A])
      {
        printf("A");
        target_speed += -2;
      }
      player.target_speed = target_speed;
    }
    else {
      player.target_speed = 0;
    }


    update_player(&player);
    check_and_push_model(&player, rect);

    printf("%f\n", player.vy);
    /*if (keys[SDL_SCANCODE_S])
      player.y += speed;
    if (keys[SDL_SCANCODE_A])
      player.x -= speed;
    if (keys[SDL_SCANCODE_D])
      player.x += speed; */

    /* Touch ground
    if (player.y + player.h >= SCREEN_HEIGHT - 50)
    {
      velocity = 0;
      jump = false;
    }
     Reset jump
    velocity += gravity * 0.16f;  // Update velocity (gravity affects it)
    player.y += velocity * 0.16f;
    printf("%b\n", jump);
    printf("%f\n", velocity);
    printf("%d\n", player.y);

    check_and_push_model(&player, rect);
    //check_and_push_model(&player, rect2);
    */

    SDL_RenderFillRect(renderer, &player.rect);

    /* Render on screen */
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
    last_time = current_time;
    //SDL_Delay(16);
  }

  /* Deinit */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
