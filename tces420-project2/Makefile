
CC = gcc
CFLAGS = -std=c11 -O2 -Wall -Wextra -I include
LDFLAGS = -pthread

all: build/single build/multi

build/single: src/single_main.c src/single.c src/matrix.c | build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

build/multi: src/multi_main.c src/multi.c src/matrix.c | build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

build:
	mkdir -p build

clean:
	rm -rf build/

.PHONY: all clean
