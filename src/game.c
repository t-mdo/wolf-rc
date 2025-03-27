#include "game.h"
#include <math.h>

void init_player(Player *player) {
  player->position.x = MAP_SIZE / 2.0f;
  player->position.y = MAP_SIZE / 2.0f;
  player->view_angle = M_PI / 2;
}
