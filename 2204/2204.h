#ifndef 2204_H
#define 2204_H

#include "../errors.h"

/*
=====204 instruction set definition=============================================
*/

/* 
----No operation----------------------------------------------------------------
    ASM Layout  NOOP
                NOOP <ignored>
    Bin Layout  0x0000000000000000
--------------------------------------------------------------------------------
*/
#define NOOP 0x0000000000000000

/* 
----Copy data from one address to another---------------------------------------
    ASM Layout  COPY 0x????????????????,0x????????????????
                COPY <64bit source address>,<64bit destination address>
    Bin Layout  0x0000000000000001
                0x????????????????
                0x????????????????
--------------------------------------------------------------------------------
*/
#define COPY 0x0000000000000001
err2204_t copy2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);
int legalCopy(int sourceDev, int destinationDev);

#endif
