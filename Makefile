CC = gcc

all: run

lists: lists.c
	$(CC) $^ -o $@

clean:
	rm lists || true

run: clean lists
	./lists
