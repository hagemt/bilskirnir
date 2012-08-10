CC=gcc
CFLAGS=-c
CXX=g++
EXE=mpirun -np 10
DFLAGS=-Wall -Wextra -g -O0
LFLAGS=-l mpi
RFLAGS=-DNDEBUG -O3

all: mpi

mpi: mpi_release
	$(EXE) mpi_release
	
mpi_debug: mpi_debug.o
	$(CC) mpi_debug.o $(LFLAGS) -o mpi_debug

mpi_debug.o: mpi.c
	$(CC) $(DFLAGS) $(CFLAGS) mpi.c -o mpi_debug.o

mpi_release: mpi_release.o
	$(CC) $(DFLAGS) mpi_release.o $(LFLAGS) -o mpi_release

mpi_release.o: mpi.c
	$(CC) $(RFLAGS) $(CFLAGS) mpi.c -o mpi_release.o

clean:
	rm -f mpi_release.o mpi_release
	rm -f mpi_debug.o mpi_debug

.PHONY: all clean mpi
