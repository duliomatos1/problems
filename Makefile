CC = gcc
FLAGS = -g

all: run

lists: lists.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm lists || true

run: clean lists
	./lists
