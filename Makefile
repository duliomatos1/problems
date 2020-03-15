CC = gcc
FLAGS = -g

all: arraylist string hashtable

arraylist: arraylist.c
	$(CC) $(FLAGS) $^ -o $@

hashtable: hashtable.c
	$(CC) $(FLAGS) $^ -o $@

string: string_problems.c
	$(CC) $(FLAGS) $^ -o $@

heap: heap.c array.o
	$(CC) $(FLAGS) $^ -o $@ -lm

sort: sort.c array.o
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) $< -c

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

run-hashtable: clean hashtable
	./hashtable

debug-hashtable: clean hashtable
	gdb ./hashtable

run-heap: clean heap
	./heap

debug-heap: clean heap
	gdb ./heap

run-sort: clean sort
	./sort

debug-sort: clean sort
	gdb ./sort
