CC=clang
CFLAGS=-lphi
LIB=-lphi

all: clear mincut

mincut:
	$(CC) mincut.c -o mincut $(LIB)

clear:
	rm -rf mincut

test:
	bash ./test.sh