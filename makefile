exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -w -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes 

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out

