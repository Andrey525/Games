all: bin/Krest-Nolik

bin/Krest-Nolik: bin build/main.o 
	g++ -no-pie build/main.o -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/main.o: build src/main.cpp
	g++ -Wall -Werror -c src/main.cpp -o $@

bin:
	mkdir bin

build: 
	mkdir build

clean:
	rm -rf bin build

.PHONY: all clean