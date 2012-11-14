# Author:  Tor E Hagemann <hagemt@rpi.edu>
# Purpose: Building a small synth project

### Variables

## commands

TAG := "composer"
SAY := $(shell which echo) -e "[$(TAG)]"
RM  := $(shell which rm) -vf
CC  := $(shell which cc)
LD  := $(shell which ld)

## flags

CFLAGS_DEBUG   := -O0 -g -pedantic
CFLAGS_RELEASE := -O3 -DNDEBUG

CFLAGS  := -Wall -Wextra -c
LDFLAGS := -lc -lm -lao

## project files

SOURCES = audio.c fft.c main.c utilities.c
OBJECTS = $(SOURCES:.c=.o)

### Targets

## phony targets

all: $(TAG)
	@$(SAY) build '$(TAG)' project

clean:
	$(RM) *.gch
	$(RM) *.o

help:
	@$(SAY) try the '$(TAG)' target

# TODO doc target(s), etc.
.PHONY: all clean help

## generic targets

%.o : %.c
	$(CC) $(CFLAGS) $+ -o $@

%.c : composer.h

## specific targets

$(TAG): $(OBJECTS)
	$(LD) $(LDFLAGS) $+ -o $@

# TODO any libs
