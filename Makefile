SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}
OUT = rotate

CC = clang
CFLAGS = -Wall -Werror -Wextra -g -O0

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	rm -rf $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJ)

re:
	make clean
	make
