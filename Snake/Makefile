bin/prog: bin build build/main.o build/circle.o build/snake.o
	g++ -no-pie build/main.o build/circle.o build/snake.o -o bin/prog -lsfml-graphics -lsfml-window -lsfml-system

build/main.o: src/main.cpp src/snake_game.hpp
	g++ -Wall -Werror -c src/main.cpp -o build/main.o

build/circle.o: src/circle.cpp src/snake_game.hpp
	g++ -Wall -Werror -c src/circle.cpp -o build/circle.o

build/snake.o: src/snake.cpp src/snake_game.hpp
	g++ -Wall -Werror -c src/snake.cpp -o build/snake.o

bin:
	mkdir bin

build: 
	mkdir build

clean: 
	rm -rf bin build

.PHONY: all clean 