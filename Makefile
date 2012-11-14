# Author:  Tor E Hagemann <hagemt@rpi.edu>
# Purpose: Building a small synth project

### Variables

## commands

TAG := composer
SAY := $(shell which echo) -e "[$(TAG)]"
RM  := $(shell which rm) -vf
CC  := $(shell which gcc)

## flags

CFLAGS_DEBUG   := -O0 -g -pedantic
CFLAGS_RELEASE := -O3 -DNDEBUG

CFLAGS  := -Wall -Wextra -fPIC $(CFLAGS_RELEASE)
LDLIBS  := -lc -lm -lao

## project files

SOURCES = audio.c fft.c main.c utilities.c
OBJECTS = $(SOURCES:.c=.o)

### Targets

## phony targets

all: $(TAG)
	@$(SAY) built '$(TAG)' project
	@$(SAY) run './$(TAG)' for fun!

clean:
	$(RM) *.gch
	$(RM) *.o
	$(RM) $(TAG)

help:
	@$(SAY) build the '$(TAG)' target

# TODO doc target(s), etc.
.PHONY: all clean help

## generic targets

%.c : %.h

%.o : %.c
	$(CC) $(CFLAGS) -c $+ -o $@

## specific targets

$(TAG): $(OBJECTS)
	$(CC) $(CFLAGS) $+ $(LDLIBS) -o $@

# TODO any libs?
