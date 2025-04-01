SRC = $(wildcard src/*.c)
OBJ = ${SRC:.c=.o}
OUT = wolf

CC = clang
CFLAGS = -Wall -Werror -Wextra -g -O0
INCLUDE_DIR = ./include
SDL_LIB_DIR = /opt/homebrew/lib
SDL_INCLUDE_DIR = /opt/homebrew/include
LIBS = SDL2

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -l$(LIBS) -L$(SDL_LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(SDL_INCLUDE_DIR) -I$(INCLUDE_DIR)

clean:
	rm -f $(OUT) $(OBJ)

re:
	make clean
	make
