CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

all: main

main: main.cpp calculator.o
	$(CXX) $(CXXFLAGS) -o main main.cpp calculator.o

calculator.o: calculator.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c calculator.cpp

clean:
	rm -f calculator.o main
