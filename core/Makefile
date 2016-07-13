all: sim

CC=g++
CFLAGS=-std=c++11 -g -pthread -fopenmp
INCLUDE=-I./include
SRC_FILES = $(wildcard ./src/*.cc)

sim:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_FILES) -o ./build/$@
	
