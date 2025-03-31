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

  int hit = 0;
  float distance_to_wall = 0;

  while (!hit) {
    // printf("cos: %f, sin: %f\n", cos_angle, sin_angle);
    float dist_x = cos_angle >= 0 ? (int)x + 1 - x : (int)x - 1 + x;
    float dist_y = sin_angle >= 0 ? (int)y + 1 - y : (int)y - 1 + y;

    float ray_dist_v = fabs(cos_angle != 0 ? dist_x / cos_angle : MAXFLOAT);
    float ray_dist_h = fabs(sin_angle != 0 ? dist_y / sin_angle : MAXFLOAT);

    /*printf("dist_x: %f, dist_y: %f, ray_dist_v: %f, ray_dist_h: %f\n", dist_x,
           dist_y, ray_dist_v, ray_dist_h);*/

    if (ray_dist_h < ray_dist_v) {
      x = x + cos_angle * ray_dist_h;
      y = sin_angle >= 0 ? (int)y + 1 : (int)y;
      distance_to_wall += ray_dist_h;
      // printf("horizontal - x: %f, y: %f\n", x, y);
      if (map[(int)y][(int)x] == 1) {
        hit = 1;
      }
    } else {
      x = cos_angle >= 0 ? (int)x + 1 : (int)x;
      y = y + sin_angle * ray_dist_v;
      distance_to_wall += ray_dist_v;
      // printf("vertical - x: %f, y: %f\n", x, y);
      if (map[(int)y][(int)x] == 1) {
        hit = 1;
      }
    }
  }

  return distance_to_wall;
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
