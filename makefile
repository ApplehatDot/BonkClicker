env:
	mkdir bin

app:
	gcc -o bin/BonkClicker.exe source/main.c -lgdi32 -lwinmm -mwindows
	echo Finished.

all:	
	make env
	make app
	