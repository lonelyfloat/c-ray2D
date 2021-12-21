SOURCE_FILES ?= src/c-ray2D.c src/main.c
FINAL_FILES = SOURCE_FILES


CFLAGS ?= -Os -std=c99 -Wall -Isrc/include -Lsrc/lib/desktop -DPLATFORM_DESKTOP
LDFLAGS ?= -lraylib

all:
	gcc -static $(SOURCE_FILES) -o game.exe $(CFLAGS) $(LDFLAGS)

lib:
	gcc -c src/c-ray2D.c -Os -std=c99 -Wall