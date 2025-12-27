#
# Makefile that builds btest and other helper programs for the CS:APP data lab
# 
CC = gcc
CFLAGS := -O0 -g -Wall -m32
LDLIBS := -lm
LDFLAGS := -m32

all: btest fshow ishow

test: btest
	@ ./btest -T100 || (echo "$$? tests fallando"; exit 1)

grade:
	./driver.pl

btest: btest.o bits.o decl.o tests.o
fshow: fshow.c
ishow: ishow.c

# Forces a recompile. Used by the driver program. 
btestexplicit:
	$(CC) $(CFLAGS) $(LDFLAGS) -o btest bits.c btest.c decl.c tests.c $(LDLIBS)

clean:
	rm -f *.o btest fshow ishow *~
