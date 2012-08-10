CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra
DFLAGS=-g -O0
LFLAGS=-l mpi
RFLAGS=-DNDEBUG -O3

all: debug_feap release_feap mpi

debug_feap: Feap.h Feap.cpp
	$(CXX) $(CXXFLAGS) $(DFLAGS) Feap.cpp -o debug_feap

release_feap: Feap.h Feap.cpp
	$(CXX) $(CXXFLAGS) $(RFLAGS) Feap.cpp -o release_feap

mpi: mpi.o
	$(CC) $(CFLAGS) mpi.o $(LFLAGS) -o mpi

mpi.o: mpi.c
	$(CC) $(CFLAGS) -c mpi.c

clean:
	rm -f debug_feap release_feap
	rm -f mpi.o mpi

.PHONY: all clean
