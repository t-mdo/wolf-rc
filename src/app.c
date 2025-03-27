#include <stdlib.h>
#include <SDL2/SDL.h>
#include "app.h"

void init_app(App* app) {
  int rendererFlags = SDL_RENDERER_ACCELERATED, windowFlags = 0;

  memset(app, 0, sizeof(App));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  app->window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

  if (!app->window) {
    printf("Failed to open %d x %d window: %s\n", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
    exit(1);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

  if (!app->renderer) {
    printf("Failed to create renderer: %s\n", SDL_GetError());
    exit(1);
  }
}
