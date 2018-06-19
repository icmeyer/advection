# This is a makefile!
# Pick a compiler
CC = g++
all: advection advection_parallel
advection: advection.cpp
	$(CC) -o advection advection.cpp -fopenmp
advection_parallel: advection_parallel.cpp
	$(CC) -o advection_prallel advection_parallel.cpp -fopenmp
