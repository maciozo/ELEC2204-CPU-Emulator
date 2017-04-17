#ifndef 2204_H
#define 2204_H

/*
=====204 instruction set definition=============================================
*/

/* 
----No operation----------------------------------------------------------------
    Layout      8   Instruction
                54  Ignored
--------------------------------------------------------------------------------
*/
#define NOOP 0x00

/* 
----Copy data from one address to another---------------------------------------
    Layout      8   Instruction
                54  Source address
--------------------------------------------------------------------------------
*/
#define CPYF 0x01

#endif
