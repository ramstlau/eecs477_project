#Setting gcc 4.7.0

PATH := /usr/um/gcc-4.7.0/bin:$(PATH)

LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64

LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

CC = g++

CFLAGS= -Wall -Werror -std=c++11

OBJS = input.o bruteforce.o

PROG = solver

all: $(PROG)
	
$(PROG): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(PROG)

clean:
	rm *.o

input.o: input.cpp
	$(CC) $(CFLAGS) -c input.cpp

bruteforce.o: input.h bruteforce.cpp
	$(CC) $(CFLAGS) -c bruteforce.cpp

