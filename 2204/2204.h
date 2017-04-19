#ifndef ISET_2204_H
#define ISET_2204_H

#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

/*
=====204 instruction set definition=============================================
*/

/* 
----No operation----------------------------------------------------------------
    ASM Layout  NOOP
    Bin Layout  0x0000000000000000
--------------------------------------------------------------------------------
*/
#define NOOP 0x0000000000000000

/* 
----Copy data from one address to another---------------------------------------
    ASM Layout  COPY <64bit source address>, <64bit destination address>
    Bin Layout  0x0000000000000001
                0x????????????????
                0x????????????????
--------------------------------------------------------------------------------
*/
#define COPY 0x0000000000000001
err2204_t copy2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString, time_t *startTime);
int legalCopy(int sourceDev, int destinationDev);

/* 
----Stop the CPU----------------------------------------------------------------
    ASM Layout  STOP
    Bin Layout  0x0000000000000002
--------------------------------------------------------------------------------
*/
#define STOP 0x0000000000000002

/* 
----Print the value of the specified address------------------------------------
    ASM Layout  PRNT <64bit address>
    Bin Layout  0x0000000000000003
                0x????????????????
--------------------------------------------------------------------------------
*/
#define PRNT 0x0000000000000003
err2204_t prnt2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString, time_t *startTime);

#endif
