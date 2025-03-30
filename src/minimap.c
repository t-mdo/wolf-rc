#include "minimap.h"

void draw_minimap(App *app, Player *player, char map[MAP_SIZE][MAP_SIZE]) {
  // Background
  SDL_Rect minimap = {.x = MINIMAP_POSITION_X,
                      .y = MINIMAP_POSITION_Y,
                      .w = MINIMAP_SIZE,
                      .h = MINIMAP_SIZE};
  SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(app->renderer, &minimap);

  // Grid
  SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
  for (int i = 0; i <= MAP_SIZE; i++) {
    SDL_Rect v_line = {.x = MINIMAP_POSITION_X + MINIMAP_CELL_SIZE * i,
                       .y = MINIMAP_POSITION_Y,
                       .w = BORDER_THICKNESS,
                       .h = MINIMAP_SIZE};
    SDL_Rect h_line = {.x = MINIMAP_POSITION_X,
                       .y = MINIMAP_POSITION_Y + MINIMAP_CELL_SIZE * i,
                       .w = MINIMAP_SIZE,
                       .h = BORDER_THICKNESS};
    SDL_RenderFillRect(app->renderer, &v_line);
    SDL_RenderFillRect(app->renderer, &h_line);
  }

  // Walls
  SDL_SetRenderDrawColor(app->renderer, 90, 90, 90, 255);
  for (int map_y = 0; map_y < MAP_SIZE; map_y++) {
    for (int map_x = 0; map_x < MAP_SIZE; map_x++) {
      if (map[map_y][map_x] == 1) {
        SDL_Rect wall_rect = {
            .x = MINIMAP_POSITION_X + MINIMAP_CELL_SIZE * map_x +
                 BORDER_THICKNESS,
            .y = MINIMAP_POSITION_Y + MINIMAP_CELL_SIZE * map_y +
                 BORDER_THICKNESS,
            .w = MINIMAP_CELL_SIZE - BORDER_THICKNESS,
            .h = MINIMAP_CELL_SIZE - BORDER_THICKNESS,
        };

        SDL_RenderFillRect(app->renderer, &wall_rect);
      }
    }
  }

  // Player
  SDL_SetRenderDrawColor(app->renderer, 200, 20, 20, 255);
  int x_rect_player_position = MINIMAP_POSITION_X +
                               MINIMAP_CELL_SIZE * player->position.x -
                               PLAYER_SQUARE_SIZE / 2;
  int y_rect_player_position = MINIMAP_POSITION_Y +
                               MINIMAP_CELL_SIZE * player->position.y -
                               PLAYER_SQUARE_SIZE / 2;

  SDL_Rect player_position_rect = {.x = x_rect_player_position,
                                   .y = y_rect_player_position,
                                   .h = PLAYER_SQUARE_SIZE,
                                   .w = PLAYER_SQUARE_SIZE};
  SDL_RenderFillRect(app->renderer, &player_position_rect);
}
