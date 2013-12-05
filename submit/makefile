PATH := /usr/um/rhel_6/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/rhel_6/gcc-4.7.0/lib64:/usr/um/rhel_6/mpc-0.9/lib/:/usr/um/rhel_6/mpfr-3.1.0/lib/:/usr/um/rhel_6/gmp-5.0.5/lib/
LD_RUN_PATH := /usr/um/rhel_6/gcc-4.7.0/lib64:/usr/um/rhel_6/mpc-0.9/lib/:/usr/um/rhel_6/mpfr-3.1.0/lib/:/usr/um/rhel_6/gmp-5.0.5/lib/

CC = LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) g++

CFLAGS= -Wall -Werror -std=c++11 -O3

OBJS = input.o greedy1.o greedy2.o bottomup.o bottomup2.o topdown.o maxdelta.o main.o
DRIVER_OBJS = input.o greedy1.o greedy2.o bruteforce2.o bottomup.o bottomup2.o topdown.o maxdelta.o driver.o validator.o

PROG = cover

all: $(PROG)

driver: $(DRIVER_OBJS)
				$(CC) $(DRIVER_OBJS) $(CFLAGS) -o driver
        
$(PROG): $(OBJS)
				$(CC) $(OBJS) $(CFLAGS) -o $(PROG)

clean: 
				rm *.o cover solver driver

tar:
				tar -pczf ../submit.tar.gz ./

input.o: input.cpp
				$(CC) $(CFLAGS) -c input.cpp

main.o: input.h greedy1.h greedy2.h main.cpp
				$(CC) $(CFLAGS) -c main.cpp

bruteforce.o: input.h bruteforce.cpp
				$(CC) $(CFLAGS) -c bruteforce.cpp

bruteforce2.o: input.h bruteforce2.h bruteforce2.cpp
				$(CC) $(CFLAGS) -c bruteforce2.cpp
			
greedy1.o: input.h greedy1.cpp
				$(CC) $(CFLAGS) -c greedy1.cpp

greedy2.o: input.h greedy1.h greedy2.cpp
				$(CC) $(CFLAGS) -c greedy2.cpp

bottomup.o: input.h bottomup.h bottomup.cpp pq.h
				$(CC) $(CFLAGS) -c bottomup.cpp

bottomup2.o: input.h bottomup2.h bottomup2.cpp pq.h coverage.h
				$(CC) $(CFLAGS) -c bottomup2.cpp

topdown.o: input.h topdown.h topdown.cpp pq.h coverage.h
				$(CC) $(CFLAGS) -c topdown.cpp

maxdelta.o: input.h maxdelta.h maxdelta.cpp pq.h coverage.h
				$(CC) $(CFLAGS) -c maxdelta.cpp

driver.o: input.h greedy1.h greedy2.h bottomup.h bottomup2.h topdown.h maxdelta.h validator.h driver.cpp 
				$(CC) $(CFLAGS) -c driver.cpp

validator.o: validator.h validator.cpp
				$(CC) $(CFLAGS) -c validator.cpp


