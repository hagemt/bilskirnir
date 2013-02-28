RM    := $(shell which rm) -vf
CC    := $(shell which gcc)
CPP   := $(shell which g++)
JAVA  := /opt/jdk1.8.0/bin/java
JAVAC := /opt/jdk1.8.0/bin/javac

CFLAGS=-Wall -Wextra -pedantic -ggdb -O0
CPPFLAGS=$(CFLAGS)

all: Palindromes.class letters mingo hacker

test: all
	$(JAVA) Palindromes # TODO make automatic, currently interactive
	echo "this is an example" | ./letters
	./mingo 100
	./hacker

clean:
	$(RM) *.o
	$(RM) *.class
	$(RM) mingo letters hacker

.PHONY: all test clean

hacker: hacker.o
	$(CC) $(CFLAGS) -std=c99 $< -o $@

mingo: mingo.o
	$(CPP) $(CFLAGS) -std=c++0x $< -o $@

letters: letters.o
	$(CPP) $(CFLAGS) -std=c++0x $< -o $@

%.class: %.java
	$(JAVAC) -source 1.8 $<

%.o: %.cpp
	$(CPP) $(CFLAGS) -std=c++0x -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -std=c99 -c $< -o $@
