all: bin build bin/flappy

bin/flappy: build/main.o build/animation.o build/bird.o build/game.o build/menu.o
	g++ -no-pie $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/main.o: src/main.cpp src/main_header.hpp
	g++ -Wall -Werror -c $< -o $@

build/animation.o: src/animation.cpp src/animation.hpp
	g++ -Wall -Werror -c $< -o $@

build/bird.o: src/bird.cpp src/bird.hpp src/animation.hpp 
	g++ -Wall -Werror -c $< -o $@

build/game.o: src/game.cpp src/main_header.hpp src/bird.hpp src/animation.hpp 
	g++ -Wall -Werror -c $< -o $@

build/menu.o: src/menu.cpp src/main_header.hpp 
	g++ -Wall -Werror -c $< -o $@

build:
	mkdir build

bin: 
	mkdir bin

clean:
	rm -rf bin build

.PHONY: all clean