# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all:  link run


link: compile
	g++ -o bin/simulation bin/main.o bin/Facility.o bin/SelectionPolicy.o bin/Settlement.o bin/Simulation.o bin/Auxiliary.o bin/Plan.o bin/Action.o

compile: clean src/Facility.cpp src/SelectionPolicy.cpp src/Settlement.cpp src/Simulation.cpp src/Auxiliary.cpp src/Plan.cpp src/main.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Facility.o src/Facility.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Settlement.o src/Settlement.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Simulation.o src/Simulation.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Plan.o src/Plan.cpp
	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/Action.o src/Action.cpp

	g++ -g -c -Wall -Weffc++ -std=c++11  -o bin/main.o src/main.cpp

clean:
	rm -rf bin/*
run:
	valgrind --leak-check=full --show-reachable=yes ./bin/simulation /workspaces/Skeleton/config_file.txt