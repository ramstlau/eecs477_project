PATH := /usr/um/rhel_6/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/rhel_6/gcc-4.7.0/lib64:/usr/um/rhel_6/mpc-0.9/lib/:/usr/um/rhel_6/mpfr-3.1.0/lib/:/usr/um/rhel_6/gmp-5.0.5/lib/
LD_RUN_PATH := /usr/um/rhel_6/gcc-4.7.0/lib64:/usr/um/rhel_6/mpc-0.9/lib/:/usr/um/rhel_6/mpfr-3.1.0/lib/:/usr/um/rhel_6/gmp-5.0.5/lib/

CXX = LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) g++

# compile cover by default
cover: my_source.cpp my_other_source.cpp
$(CXX) -O3 -std=c++11 my_source.cpp my_other_source.cpp -o cover
