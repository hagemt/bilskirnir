CC=g++
CFLAGS=-Wall -Wextra
DFLAGS=-g -O0
RFLAGS=-DNDEBUG -O3

all: debug_feap release_feap

debug_feap:
	$(CC) $(CFLAGS) $(DFLAGS) Feap.cpp -o debug_feap

release_feap:
	$(CC) $(CFLAGS) $(DFLAGS) Feap.cpp -o release_feap

.PHONY: all
