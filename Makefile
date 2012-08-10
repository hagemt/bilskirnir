CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra
DFLAGS=-g -O0
LFLAGS=
RFLAGS=-DNDEBUG -O3

all: debug_feap release_feap

debug_feap: Feap.h Feap.cpp
	$(CXX) $(CXXFLAGS) $(DFLAGS) Feap.cpp -o debug_feap

release_feap: Feap.h Feap.cpp
	$(CXX) $(CXXFLAGS) $(RFLAGS) Feap.cpp -o release_feap

clean:
	rm -f debug_feap release_feap

.PHONY: all clean
