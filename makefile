# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean link

link: compile
	g++ -o bin/main bin/main.o bin/Facility.o bin/SelectionPolicy.o

compile: src/test.cpp src/Facility.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/main.o src/main.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Facility.o src/Facility.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
clean:
	rm -rf bin/*