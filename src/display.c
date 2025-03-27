#include "display.h"
#include <SDL2/SDL.h>
#include <math.h>

void draw_ceiling_and_floor(App *app) {
  SDL_Rect ceiling = {
      .x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT / 2};
  SDL_Rect floor = {.x = 0,
                    .y = WINDOW_HEIGHT / 2,
                    .w = WINDOW_WIDTH,
                    .h = WINDOW_HEIGHT / 2};

  SDL_SetRenderDrawColor(app->renderer, CEILING_COLOR_R, CEILING_COLOR_G,
                         CEILING_COLOR_B, 255);
  SDL_RenderFillRect(app->renderer, &ceiling);
  SDL_SetRenderDrawColor(app->renderer, FLOOR_COLOR_R, FLOOR_COLOR_G,
                         FLOOR_COLOR_B, 255);
  SDL_RenderFillRect(app->renderer, &floor);
}

float get_wall_distance(Player *player, char map[MAP_SIZE][MAP_SIZE],
                        float angle) {
  const float step_size = 0.1f;
  int x;
  int y;
  float dir_x = cos(angle);
  float dir_y = sin(angle);
  char hit_bool = 0;
  float step = 0;

  while (!hit_bool) {
    x = (int)(player->position.x + step * dir_x);
    y = (int)(player->position.y + step * dir_y);
    /*printf("x: %d, y: %d, dir_x: %f, dir_y: %f, step: %f, theta: %f\n", x, y,
           dir_x, dir_y, step, angle);*/
    if (map[y][x] == 1)
      hit_bool = 1;
    step += step_size;
  }
  /*printf(
      "HIT A WALL! x: %d, y: %d, dir_x: %f, dir_y: %f, step: %f, theta: %f\n",
      x, y, dir_x, dir_y, step, angle);*/
  return step;
}

void draw_wall_column(App *app, int column_index, float distance) {
  int wall_size = WINDOW_HEIGHT / distance;
  int start_y = WINDOW_HEIGHT / 2 - wall_size / 2;

  SDL_Rect wall = {.x = column_index, .y = start_y, .w = 1, .h = wall_size};
  SDL_SetRenderDrawColor(app->renderer, WALL_COLOR_R, WALL_COLOR_G,
                         WALL_COLOR_B, 255);
  SDL_RenderFillRect(app->renderer, &wall);
}

void draw_walls(App *app, Player *player, char map[MAP_SIZE][MAP_SIZE]) {
  float distance;
  float increment = (float)FOV_ANGLE / W_RESOLUTION;
  float theta;

  for (int i = 0; i < W_RESOLUTION; i++) {
    theta = player->view_angle - (float)FOV_ANGLE / 2 + i * increment;
    distance = get_wall_distance(player, map, theta);
    // printf("distance %f\n", distance);
    draw_wall_column(app, i, distance);
  }
}

void display(App *app, Player *player, char map[MAP_SIZE][MAP_SIZE]) {
  draw_ceiling_and_floor(app);
  draw_walls(app, player, map);
  SDL_RenderPresent(app->renderer);
  SDL_Delay(16);
}
