CC=c99
CFLAGS=-Wall -Wextra  -z noexecstack -pedantic -Wno-unused-variable -Wno-unused-parameter -Wno-missing-field-initializers -Wfloat-conversion -O0 -ggdb -no-pie -lm
NASM=nasm
NASMFLAGS=-f elf64 -g -F DWARF 

TARGETS=main unit_tester intensive_tester game
all: $(TARGETS)

main: main.c lib_c.o lib_asm.o
	$(CC) $(CFLAGS) $^ -o $@

intensive_tester: intensive_tests.c lib_c.o lib_asm.o optparser.o
	$(CC) $(CFLAGS) $^ -o $@

unit_tester: unit_tests.c lib_c.o lib_asm.o
	$(CC) $(CFLAGS) $^ -o $@

game: game.c lib_c.o lib_asm.o
	$(CC) $(CFLAGS) $^ -o $@

optparser.o: optparser.c
	$(CC) $(CFLAGS) -c $< -o $@

lib_c.o: lib.c
	$(CC) $(CFLAGS) -c $< -o $@

lib_asm.o: lib.asm
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f $(TARGETS)
	rm -f salida.propios.caso*
	rm -f gameResult*

