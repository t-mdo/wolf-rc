#ifndef APP_H_
# define APP_H_

# include <SDL2/SDL.h>
# define WINDOW_NAME "Wolf RC"
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

typedef struct App {
  SDL_Renderer *renderer;
  SDL_Window *window;
} App;

void init_app(App* app);

#endif
