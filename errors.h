#ifndef ERRORS_2204_H
#define ERRORS_2204_H

#include <stdint.h>

/* The operation completed successfully */
#define SUCCESS 0

/* The target address is outside of the boundaries of the device's memory addresses */
#define ERR_ADDRESS_OUT_OF_RANGE -1

/*
    The end address is outside of the boundaries of the device's memory addresses.
    Length is probably too long.
*/
#define ERR_END_ADDRESS_OUT_OF_RANGE -2

/* The specified address or range of addresses is already in use */
#define ERR_RAM_ADDRESS_IN_USE -3

/* The specified address is invalid. Most likely no device owns that address */
#define ERR_INVALID_ADDRESS -4

/*
    Cannot copy from the specified source address to the specified destination address.
    Most likely because the program attempted to copy data without going through the CPU registers.
*/
#define ERR_ILLEGAL_MEMORY_COPY -5

/* The program tried to copy data to an invalid address */
#define ERR_COPY_TO_INVALID -6

/* The program tried to read data from an invalid address */
#define ERR_READ_FROM_INVALID -7

/* The program received an unexpected result from a function */
#define ERR_UNEXPECTED_RESULT -8

/* The specified instruction has not been defined */
#define ERR_UNKNOWN_INSTRUCTION -9


typedef struct
{
    int errno;
    uint64_t address;
} err2204_t;

#endif
