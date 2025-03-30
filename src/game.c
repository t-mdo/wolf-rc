#include "game.h"
#include <math.h>

void init_player(Player *player) {
  player->position.x = 8.5;
  player->position.y = 8.5;
  player->view_angle = M_PI / 2;
}

void rotate_player(Player *player, int cw_sense) {
  if (cw_sense)
    player->view_angle += fmod(M_PI / 90, 2 * M_PI);
  else
    player->view_angle -= fmod(M_PI / 90, 2 * M_PI);
}

void move_player(Player *player, int forward_direction) {
  float dir_x = cos(player->view_angle);
  float dir_y = sin(player->view_angle);

  if (forward_direction) {
    player->position.x += 0.5 * dir_x;
    player->position.y += 0.5 * dir_y;
  } else {
    player->position.x -= 0.5 * dir_x;
    player->position.y -= 0.5 * dir_y;
  }
}
