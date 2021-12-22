all:
	gcc -c src/c-ray2D.c -Os -std=c99 -Wall && ar -rc libc-ray2D.a c-ray2D.o
