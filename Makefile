CC = gcc
FLAGS = -g

all: run

arraylist: arraylist.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm arraylist || true

run: clean arraylist
	./arraylist
