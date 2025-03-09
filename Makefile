CC=gcc

CFLAGS=-Wall -Werror -std=c99 -lSDL2 -g -lm -lSDL2_image
SRC=$(wildcard src/*.c)

format:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i

build: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)
