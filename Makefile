CC=gcc
CFLAGS=-Wall -Wextra  -pedantic -std=c99 -g 
INCLUDE=-I./include -I/usr/local/Cellar/readline/8.2.13/include -D_DARWIN_C_SOURCE
LDFLAGS=-L/usr/local/Cellar/readline/8.2.13/lib -lreadline

 
FILES=$(wildcard src/*.c)
OBJS=$(FILES:.c=.o)
OBJS:=$(OBJS:src/%=build/%)
BUILD_DIR=build/



all: make_dir build/main

make_dir:
	mkdir -p $(BUILD_DIR)

build/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

build/main: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $^ -o $@

run: all
	./build/main

clean:
	rm -rf $(BUILD_DIR)
