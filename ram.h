#ifndef RAM_2204_H
#define RAM_2204_H

#include <stdint.h>

/* State that says an address is free */
#define RAM_FREE 0

/* State that says an address is in use */
#define RAM_USED 1

typedef struct
{
    /* First memory address */
    uint8_t address;

    /* Size of the RAM. ramSize*64 bits */
    uint64_t size;

    /* The RAM array itself */
    uint64_t *ram;

    /* Stores the state of each memory address */
    uint8_t *states;

    /* The last memory address */
    uint64_t addressMax;
} ram_t;

/*
====Initialise RAM device=======================================================
    ramAddress:     First memory address of the RAM.
    ramSize:        Size of the RAM device in blocks of 64 bits.
    *ramDevice:     Pointer to the desired ram_t instance.
====================
    Returns NULL
================================================================================
*/
void ramInit(uint8_t ramAddress, uint64_t ramSize, ram_t *ramDevice);

/*
====Read single word from RAM===================================================
    *ramDevice:     Pointer to the desired RAM instance.
    address:        RAM address to read from.
    *readTo:        Pointer in which to store the read data.
====================
    Returns         ERR_ADDRESS_OUT_OF_RANGE
                    SUCCESS
================================================================================
*/
int ramRead(ram_t *ramDevice, uint64_t address, uint64_t *readTo);

/*
====Read multiple words from RAM================================================
    *ramDevice:     Pointer to the desired RAM instance.
    address:        RAM address to start reading from.
    *readTo:        Pointer in which to store the read data.
    length:         Number of 64 bit words to read.
====================
    Returns:        ERR_ADDRESS_OUT_OF_RANGE
                    ERR_END_ADDRESS_OUT_OF_RANGE
                    SUCCESS
================================================================================
*/
int ramReadBurst(ram_t *ramDevice, uint64_t address, uint64_t *readTo, uint64_t length);

/*
====Write single word to RAM====================================================
    *ramDevice:     Pointer to the desired RAM instance.
    address:        RAM address to write to.
    data:           Word to write to the specified RAM address.
====================
    Returns         ERR_ADDRESS_OUT_OF_RANGE
                    ERR_RAM_ADDRESS_IN_USE
                    SUCCESS
================================================================================
*/
int ramWrite(ram_t *ramDevice, uint64_t address, uint64_t data);

/*
====Write multiple words to RAM=================================================
    *ramDevice:     Pointer to the desired RAM instance.
    address:        RAM address to start writing from.
    *writeFrom:     Pointer to the data to be written.
    length:         Number of 64 bit words to write.
====================
    Returns:        ERR_ADDRESS_OUT_OF_RANGE
                    ERR_END_ADDRESS_OUT_OF_RANGE
                    ERR_RAM_ADDRESS_IN_USE
                    SUCCESS
================================================================================
*/
int ramWriteBurst(ram_t *ramDevice, uint64_t ramAddress, uint64_t *writeFrom, uint64_t length);

/*
====Free RAM addresses for writing==============================================
    *ramDevice:     Pointer to the desired RAM instance.
    address:        RAM address to start freeing from.
    length:         Amount of addresses to free.
====================
    Returns         ERR_ADDRESS_OUT_OF_RANGE
                    ERR_END_ADDRESS_OUT_OF_RANGE
                    SUCCESS
================================================================================
*/
int ramFree(ram_t *ramDevice, uint64_t address, uint64_t length)

/*
====Get the state of a range of RAM addresses===================================
    *ramDevice:     Pointer to the desired RAM instance.
    address:        RAM address to start from.
    length:         Amount of addresses to check.
====================
    Returns         ERR_ADDRESS_OUT_OF_RANGE
                    ERR_END_ADDRESS_OUT_OF_RANGE
                    RAM_USED
                    RAM_FREE
================================================================================
*/
int ramState(ram_t *ramDevice, uint64_t address, uint64_t length);

#endif
