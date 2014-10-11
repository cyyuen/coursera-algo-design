CC=clang
CFLAGS=-c -Wall

all: clean mincut

mincut:
	$(CC) mincut.c ../lib/stack.c -o mincut

clean:
	rm -rf mincut

test:
	bash ./test.sh