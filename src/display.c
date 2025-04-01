#include "display.h"
#include "minimap.h"
#include <SDL2/SDL.h>
#include <math.h>

void draw_ceiling_and_floor(App *app) {
  SDL_Rect ceiling = {.x = 0, .y = 0, .w = W_RESOLUTION, .h = H_RESOLUTION / 2};
  SDL_Rect floor = {
      .x = 0, .y = H_RESOLUTION / 2, .w = W_RESOLUTION, .h = H_RESOLUTION / 2};

  SDL_SetRenderDrawColor(app->renderer, CEILING_COLOR_R, CEILING_COLOR_G,
                         CEILING_COLOR_B, 255);
  SDL_RenderFillRect(app->renderer, &ceiling);
  SDL_SetRenderDrawColor(app->renderer, FLOOR_COLOR_R, FLOOR_COLOR_G,
                         FLOOR_COLOR_B, 255);
  SDL_RenderFillRect(app->renderer, &floor);
}

float trace_ray_to_wall(Player *player, char map[MAP_SIZE][MAP_SIZE],
                        float angle) {
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);

  float x = player->position.x;
  float y = player->position.y;

  int map_x = (int)x;
  int map_y = (int)y;

  int step_x = (cos_angle >= 0) ? 1 : -1;
  int step_y = (sin_angle >= 0) ? 1 : -1;

  float delta_dist_x = fabs(1.0f / cos_angle);
  float delta_dist_y = fabs(1.0f / sin_angle);

  float side_dist_x = (step_x > 0) ? ((int)(x + 1) - x) * delta_dist_x
                                   : (x - (int)x) * delta_dist_x;
  float side_dist_y = (step_y > 0) ? ((int)(y + 1) - y) * delta_dist_y
                                   : (y - (int)y) * delta_dist_y;

  while (side_dist_x < MAX_RAY_DIST || side_dist_y < MAX_RAY_DIST) {
    if (side_dist_x < side_dist_y) {
      map_x += step_x;
      if (map[map_y][map_x] == 1)
        return side_dist_x;
      side_dist_x += delta_dist_x;
    } else {
      map_y += step_y;
      if (map[map_y][map_x] == 1)
        return side_dist_y;
      side_dist_y += delta_dist_y;
    }
  }
  return MAX_RAY_DIST;
}

void draw_wall_column(App *app, int column_index, float distance) {
  int wall_size = H_RESOLUTION / distance;
  int start_y = H_RESOLUTION / 2 - wall_size / 2;

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
    distance = trace_ray_to_wall(player, map, theta);
    // printf("distance %f\n", distance);
    draw_wall_column(app, i, distance);
  }
}

void display(App *app, Player *player, char map[MAP_SIZE][MAP_SIZE]) {
  draw_ceiling_and_floor(app);
  draw_walls(app, player, map);
  draw_minimap(app, player, map);
  SDL_RenderPresent(app->renderer);
  SDL_Delay(16);
}
