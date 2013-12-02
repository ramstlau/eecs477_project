PATH := /usr/um/rhel_6/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/rhel_6/gcc-4.7.0/lib64:/usr/um/rhel_6/mpc-0.9/lib/:/usr/um/rhel_6/mpfr-3.1.0/lib/:/usr/um/rhel_6/gmp-5.0.5/lib/
LD_RUN_PATH := /usr/um/rhel_6/gcc-4.7.0/lib64:/usr/um/rhel_6/mpc-0.9/lib/:/usr/um/rhel_6/mpfr-3.1.0/lib/:/usr/um/rhel_6/gmp-5.0.5/lib/

CC = LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) g++

CFLAGS= -Wall -Werror -std=c++11 -O3

OBJS = input.o greedy1.o greedy2.o main.o

PROG = cover

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

