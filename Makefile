main: main.c
	gcc  main.c -o main -Iinclude -Llib -lraylib -lm -lopengl32 -lgdi32 -lwinmm
