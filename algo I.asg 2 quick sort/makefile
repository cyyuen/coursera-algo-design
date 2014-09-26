CC=clang
CFLAGS=-c -Wall

all: clean ex1 ex2 ex3

ex1:
	$(CC) qsort_core.c pivot_in_first.c -o ex1

ex2:
	$(CC) qsort_core.c pivot_in_last.c -o ex2

ex3:
	$(CC) qsort_core.c pivot_in_median.c -o ex3

clean:
	rm -rf ex*

test:
	bash ./test.sh