CC = gcc
CFLAGS = -g -Wall -Wpedantic -Wno-pedantic-ms-format
LIBCONFIG = ./libconfig

emulator: emulator.c cpu.c ram.c errors.c ./2204/*.c emulator.h cpu.h ram.h errors.h ./2204/*.h
	$(CC) $(CFLAGS) -o 2204 emulator.c cpu.c ram.c errors.c ./2204/2204.c -L$(LIBCONFIG)/lib/.libs -lconfig
	cp $(LIBCONFIG)/lib/.libs/libconfig-9.dll ./libconfig-9.dll
	cp $(LIBCONFIG)/lib/.libs/libconfig.a ./libconfig.a

assembler: assembler.c assembler.h errors.h ./2204/2204.h
	$(CC) $(CFLAGS) -o assembler assembler.c errors.c -std=gnu99
