#ifndef GAME_H_
# define GAME_H_

# define MAP_SIZE 16

typedef struct Coordinates2D {
  float x;
  float y;
} Coordinates2D;

typedef struct Player {
  Coordinates2D position;
  float view_angle;
} Player;

void init_player(Player* player);

#endif
