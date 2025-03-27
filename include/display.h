#ifndef DISPLAY_H_
# define DISPLAY_H_

# include "app.h"
# include "game.h"
# include <math.h>

# define FLOOR_COLOR_R 124
# define FLOOR_COLOR_G 202
# define FLOOR_COLOR_B 0
# define CEILING_COLOR_R 135
# define CEILING_COLOR_G 206
# define CEILING_COLOR_B 235
# define WALL_COLOR_R 80
# define WALL_COLOR_G 80
# define WALL_COLOR_B 80

# define FOV_ANGLE (M_PI / 3) // 60 degrees
# define W_RESOLUTION WINDOW_WIDTH
# define H_RESOLUTION WINDOW_HEIGHT

void display(App* app, Player* player, char map[MAP_SIZE][MAP_SIZE]);

#endif
