env:
	mkdir obj
	mkdir bin

all:
	gcc -o bin/BonkClicker.exe source/main.c -lgdi32 -lwinmm -mwindows