# Author:  Tor E Hagemann <hagemt@rpi.edu>
# Purpose: Building a small synth project

### Variables

## commands

TAG  := composer
TYPE := RELEASE

SAY := $(shell which echo) -e "[$(TAG)]"
RM  := $(shell which rm) -vf
CC  := $(shell which gcc)
CXX := $(shell which g++)
LD  := $(shell which ld)
PC  := $(shell which pkg-config)

## flags

CFLAGS_TCLAP   := $(shell $(PC) --cflags tclap)
CFLAGS_CPPUNIT := $(shell $(PC) --cflags cppunit)
CFLAGS_INCLUDE := $(CFLAGS_CPPUNIT) $(CFLAGS_TCLAP)

CFLAGS_DEBUG   := -O0 -g -pedantic -Wno-variadic-macros
CFLAGS_RELEASE := -O3 -DNDEBUG
CFLAGS_EXTRA   := $(CLFAGS_INCLUDE) $(CFLAGS_$(TYPE))
CFLAGS         := -Wall -Wextra -fPIC $(CFLAGS_EXTRA)
CXXFLAGS       := -Wall -Wextra       $(CFLAGS_EXTRA)

LDFLAGS        := -shared -L .
LDLIBS         := -lc -lm -lao -lsndfile $(shell $(PC) --libs cppunit)

## project files

LIB_SOURCES = audio.c fft.c log.c utilities.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

### Targets

## phony targets

all: $(TAG)
	@$(SAY) built '$(TAG)' project
	@$(SAY) run './$(TAG)' for fun!

clean:
	$(RM) *.gch
	$(RM) *.o
	$(RM) *.so
	$(RM) $(TAG) lender

help:
	@$(SAY) build the '$(TAG)' target

# TODO doc target(s), etc.
.PHONY: all clean help

## generic targets

%.c : %.h

%.o : %.c
	$(CC) $(CFLAGS) -c $+ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $+ -o $@

## specific targets

$(TAG): $(LIB_OBJECTS) main.o
	$(CC) $(CFLAGS) $+ $(LDLIBS) -o $@

libender.so: $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) $+ $(LDLIBS) -o $@

lender: libender.so client.o settings.o
	$(CXX) $(CXXFLAGS) client.o settings.o $(LDLIBS) -lender -o lender

# TODO any more libs?
