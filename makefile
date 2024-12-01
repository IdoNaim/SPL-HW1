# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean link

link: compile
	g++ -o bin/test bin/test.o bin/Settlement.o

compile: src/test.cpp src/Settlement.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/test.o src/test.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Settlement.o src/Settlement.cpp
clean:
	rm -rf bin/*