CC=clang
CFLAGS=-Wall -shared -undefined dynamic_lookup

all: clear libphi

libphi:
	$(CC) $(CFLAGS) -o libphi.so randset.c hashtbl.c list.c

clear:
	rm -rf *.so

install:
	cp *.h /usr/local/include/phi/
	cp libphi.so /usr/local/lib/

uninstall:
	rm /usr/local/include/phi/*
	rm /usr/local/lib/libphi.so

test:
	bash ./test.sh