CC = gcc
FLAGS = -g

all: arraylist string

arraylist: arraylist.c
	$(CC) $(FLAGS) $^ -o $@

string: string_problems.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm arraylist || true
	rm string || true

run-array: clean arraylist
	./arraylist

debug-array: clean arraylist
	gdb ./arraylist

run-string: clean string
	./string

debug-string: clean string
	gdb ./string
