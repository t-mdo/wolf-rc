#ifndef MINIMAP_H_
# define MINIMAP_H_

#include "app.h"
#include "game.h"
#include "display.h"

# define MINIMAP_SIZE 224
# define MINIMAP_CELL_SIZE MINIMAP_SIZE / MAP_SIZE
# define MINIMAP_POSITION_X WINDOW_WIDTH - MINIMAP_SIZE
# define MINIMAP_POSITION_Y 0

#define BORDER_THICKNESS 1
#define PLAYER_SQUARE_SIZE 8

void draw_minimap(App *app, Player *player, char map[MAP_SIZE][MAP_SIZE]);

#endif
