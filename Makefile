#Setting gcc 4.7.0

PATH := /usr/um/gcc-4.7.0/bin:$(PATH)

LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64

LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

CC = g++

CFLAGS= -Wall -Werror -std=c++11 -g

OBJS = input.o greedy1.o greedy2.o driver.o

PROG = solver

all: $(PROG)
	
$(PROG): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(PROG)

clean:
	rm *.o

input.o: input.cpp
	$(CC) $(CFLAGS) -c input.cpp

main.o: input.h greedy1.h greedy2.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp

bruteforce.o: input.h bruteforce.cpp
	$(CC) $(CFLAGS) -c bruteforce.cpp
	
greedy1.o: input.h greedy1.cpp
	$(CC) $(CFLAGS) -c greedy1.cpp

greedy2.o: input.h greedy1.h greedy2.cpp
	$(CC) $(CFLAGS) -c greedy2.cpp

driver.o: driver.cpp
	$(CC) $(CFLAGS) -c driver.cpp

