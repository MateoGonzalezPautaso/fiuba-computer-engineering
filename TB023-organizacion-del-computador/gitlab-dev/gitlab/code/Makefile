CC:=gcc
CFLAGS:=-Wall -Wextra -g

.PHONY: all clean
TARGET:=main tester

all: $(TARGET)

lib.o: lib.c lib.h 
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c lib.h
	$(CC) $(CFLAGS) -c $< -o $@

tester.o: tester.c
	$(CC) $(CFLAGS) -c $< -o $@

main: main.o lib.o
	$(CC) $(CFLAGS) $^ -o $@

tester: tester.o lib.o
	$(CC) $(CFLAGS) $^ -lcriterion -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)