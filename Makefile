
CC=g++
CFLAGS=-lcrypto

all: 
	$(CC) hash_it.cpp $(CFLAGS) -o hashit

clean:
	rm -f *~ hashit *.o

install:
	cp hashit /usr/bin/
