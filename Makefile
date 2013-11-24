CFLAGS=-std=c++11

all: input.o
	g++ $(CFLAGS) -o solver input.o

clean:
	rm *.o

input.o: input.cpp
	g++ $(CFLAGS) -c input.cpp
