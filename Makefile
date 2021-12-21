SOURCE_FILES ?= src/raycast.c src/main.c
PLATFORM ?= PLATFORM_DESKTOP
FINAL_FILES = SOURCE_FILES


CFLAGS ?= -Os -std=c99 -Wall -Isrc/include -Lsrc/lib/desktop -DPLATFORM_DESKTOP
WEBFLAGS =  -Os -std=c99 -Wall -Isrc/include -Lsrc/lib/web -s USE_GLFW=3 -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file template.html  # --preload-file assets
RAYLIB_LOC = src/lib/desktop
LDFLAGS ?= -lraylib
COMMAND ?= gcc -static $(SOURCE_FILES) -o game.exe $(CFLAGS) $(LDFLAGS)

ifeq ($(PLATFORM), PLATFORM_WEB)
	FINAL_FILES := $(patsubst main, web, $(SOURCE_FILES))
	COMMAND = emcc $(SOURCE_FILES) -o game.html $(WEBFLAGS) $(LDFLAGS)
endif
ifeq ($(PLATFORM), PLATFORM_DESKTOP)
	FINAL_FILES := $(patsubst web, main, $(SOURCE_FILES))
	LDFLAGS += -lopengl32 -lgdi32 -lwinmm
	COMMAND = gcc -static $(SOURCE_FILES) -o game.exe $(CFLAGS) $(LDFLAGS)
endif

all:
	$(COMMAND)

lib:
	gcc -c src/raycast.c -Os -std=c99 -Wall