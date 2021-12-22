CC = cc

ifeq ($(OS), Windows_NT)
	CC = gcc
else
	CC = cc
endif

all:
	$(CC) -c src/c-ray2D.c -Os -std=c99 -Wall && ar -rc libc-ray2D.a c-ray2D.o
