CFLAGS=-std=c++11

all: solver.o
	g++ $(CFLAGS) -o solver solver.o

clean:
	rm *.o

solver.o: solver.cpp
	g++ $(CFLAGS) -c solver.cpp
