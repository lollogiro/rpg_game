all: main

main: main.cpp
all: main

main: main.cpp
	g++ *.cpp -lncurses -o test

clean:
	rm -rf *.o