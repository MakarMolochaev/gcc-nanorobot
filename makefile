CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = nanorobot
SRC = nanorobot.c

nanorobot: nanorobot.c
	gcc -o nanorobot nanorobot.c

clean:
	rm -f nanorobot

.PHONY: all clean