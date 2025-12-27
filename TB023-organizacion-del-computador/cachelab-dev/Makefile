CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -O0 -ggdb -no-pie -debug
LIBS:=-lm

all: cachesim 

cachesim: traza.o cachesim.o simulador.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

cachesim.o: cachesim.c
	$(CC) $(CFLAGS) -c $^ -o $@

simulador.o: simulador.c
	$(CC) $(CFLAGS) -c $^ -o $@

traza.o: traza.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o
	rm -f cachesim
	rm -f traza
	rm -f simulador
	

