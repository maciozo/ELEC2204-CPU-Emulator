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
    Note        Copy operations must be between either
                    Register <-> Register
                    Device <-> Register
                Copying between devices is not permittd
--------------------------------------------------------------------------------
*/
#define COPY 0x0000000000000001
err2204_t copy2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);
int legalCopy(int sourceDev, int destinationDev);

/*
----Stop the CPU----------------------------------------------------------------
    ASM Layout  STOP
    Bin Layout  0x0000000000000002
--------------------------------------------------------------------------------
*/
#define STOP 0x0000000000000002

/*
----Print the hex value of the specified address--------------------------------
    ASM Layout  PRNT <64bit address>
    Bin Layout  0x0000000000000003
                0x????????????????
--------------------------------------------------------------------------------
*/
#define PRNT 0x0000000000000003
err2204_t prnt2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----Set the programme counter to the specified address--------------------------
    ASM Layout  JUML <64bit address>
    Bin Layout  0x0000000000000004
                0x????????????????
--------------------------------------------------------------------------------
*/
#define JUML 0x0000000000000004
err2204_t juml2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----Store data at the specified address-----------------------------------------
    ASM Layout  STOR <64bit address>, <64bit data>
    Bin Layout  0x0000000000000005
                0x????????????????
                0x????????????????
--------------------------------------------------------------------------------
*/
#define STOR 0x0000000000000005
err2204_t stor2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----Free the specified memory address range-------------------------------------
    ASM Layout  FREE <64bit data>, <64bit length>
    Bin Layout  0x0000000000000006
                0x????????????????
                0x????????????????
--------------------------------------------------------------------------------
*/
#define FREE 0x0000000000000006
err2204_t free2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----Add values from first 2 addresses, store in third---------------------------
    ASM Layout  ADDA <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x0000000000000007
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define ADDA 0x0000000000000007
err2204_t adda2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----Subtract the value at the 2nd address from the 1st. Store result in 3rd-----
    ASM Layout  SUBA <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x0000000000000008
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define SUBA 0x0000000000000008
err2204_t suba2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----Print the unsigned decimal value of the specified address-------------------
    ASM Layout  PRND <64bit address>
    Bin Layout  0x0000000000000009
                0x????????????????
--------------------------------------------------------------------------------
*/
#define PRND 0x0000000000000009
err2204_t prnd2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----OR the value at the 1st address with the 2nd. Store result in 3rd-----------
    ASM Layout  ORAD <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x000000000000000A
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define ORAD 0x000000000000000A
err2204_t orad2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----AND the value at the 1st address with the 2nd. Store result in 3rd----------
    ASM Layout  ANDA <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x000000000000000C
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define ANDA 0x000000000000000B
err2204_t anda2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----NOT the value at the 1st address. Store result in the 2nd-------------------
    ASM Layout  ANDA <64bit address>, <64bit address>
    Bin Layout  0x000000000000000C
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define NOTA 0x000000000000000C
err2204_t nota2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----NAND the value at the 1st address with the 2nd. Store result in 3rd---------
    ASM Layout  NNDA <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x000000000000000D
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define NNDA 0x000000000000000D
err2204_t nanda2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----NOR the value at the 1st address with the 2nd. Store result in 3rd----------
    ASM Layout  NORA <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x000000000000000E
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define NORA 0x000000000000000E
err2204_t nora2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

/*
----XOR the value at the 1st address with the 2nd. Store result in 3rd----------
    ASM Layout  XORA <64bit address>, <64bit address>, <64bit address>
    Bin Layout  0x000000000000000F
                0x????????????????
                0x????????????????
                0x????????????????
    Note        Both operands must be in the CPU registers
                Can be written back to any device
--------------------------------------------------------------------------------
*/
#define XORA 0x000000000000000F
err2204_t xora2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

#endif
