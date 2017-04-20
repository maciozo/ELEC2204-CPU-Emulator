CC = gcc
CFLAGS = -g -Wall -Wpedantic -Wno-pedantic-ms-format

emulator: emulator.c cpu.c ram.c errors.c ./2204/*.c emulator.h cpu.h ram.h errors.h ./2204/*.h
	$(CC) $(CFLAGS) -o 2204 emulator.c cpu.c ram.c errors.c ./2204/2204.c -L./libconfig/lib/.libs -lconfig

assembler: assembler.c errors.h ./2204/2204.h
	$(CC) $(CFLAGS) -o assembler assembler.c errors.c -std=gnu99
