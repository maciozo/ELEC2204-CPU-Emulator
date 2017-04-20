#ifndef ERRORS_2204_H
#define ERRORS_2204_H

#include <stdint.h>

/* The operation completed successfully */
#define SUCCESS 0
#define SUCCESS_STR "The operation completed successfully. (SUCCESS)"

/* The target address is outside of the boundaries of the device's memory addresses */
#define ERR_ADDRESS_OUT_OF_RANGE -1
#define ERR_ADDRESS_OUT_OF_RANGE_STR "The specified destination address is out of range. (ERR_ADDRESS_OUT_OF_RANGE)"

/*
    The end address is outside of the boundaries of the device's memory addresses.
    Length is probably too long.
*/
#define ERR_END_ADDRESS_OUT_OF_RANGE -2
#define ERR_END_ADDRESS_OUT_OF_RANGE_STR "The specified end address is out of range. (ERR_END_ADDRESS_OUT_OF_RANGE)"

/* The specified address or range of addresses is already in use */
#define ERR_RAM_ADDRESS_IN_USE -3
#define ERR_RAM_ADDRESS_IN_USE_STR "The specified RAM address is already in use. (ERR_RAM_ADDRESS_IN_USE)"

/* The specified address is invalid. Most likely no device owns that address */
#define ERR_INVALID_ADDRESS -4
#define ERR_INVALID_ADDRESS_STR "The specified address is invalid. (ERR_INVALID_ADDRESS)"

/*
    Cannot copy from the specified source address to the specified destination address.
    Most likely because the program attempted to copy data without going through the CPU registers.
*/
#define ERR_ILLEGAL_MEMORY_COPY -5
#define ERR_ILLEGAL_MEMORY_COPY_STR "Cannot copy from the specified source address to the specified destination address. Most likely because the program attempted to copy data without going through the CPU registers. (ERR_ILLEGAL_MEMORY_COPY)"

/* The program tried to copy data to an invalid address */
#define ERR_COPY_TO_INVALID -6
#define ERR_COPY_TO_INVALID_STR "The program tried to copy data to an invalid address. (ERR_COPY_TO_INVALID)"

/* The program tried to read data from an invalid address */
#define ERR_READ_FROM_INVALID -7
#define ERR_READ_FROM_INVALID_STR "The program tried to read data from an invalid address. (ERR_READ_FROM_INVALID)"

/* The program received an unexpected result from a function */
#define ERR_UNEXPECTED_RESULT -8
#define ERR_UNEXPECTED_RESULT_STR "The program received an unexpected result from a function. (ERR_UNEXPECTED_RESULT)"

/* The specified instruction has not been defined */
#define ERR_UNKNOWN_INSTRUCTION -9
#define ERR_UNKNOWN_INSTRUCTION_STR "The program received an undefined instruction. (ERR_UNKNOWN_INSTRUCTION)"

/* Program exited the main CPU loop for some reason */
#define ERR_CPU_BREAK -10
#define ERR_CPU_BREAK_STR "The program exited the main CPU loop for some reason. (ERR_CPU_BREAK)"

/* The specified address is too high */
#define ERR_ADDRESS_TOO_HIGH -11
#define ERR_ADDRESS_TOO_HIGH_STR "The program tried to access data from an address beyond the device's range. (ERR_ADDRESS_TOO_HIGH)"

/* The specified address is too low */
#define ERR_ADDRESS_TOO_LOW -12
#define ERR_ADDRESS_TOO_LOW_STR "The program tried to access data from an address BELOW the device's range. (ERR_ADDRESS_TOO_LOW)"

typedef struct
{
    int errnum;
    uint64_t address;
} err2204_t;

void printError(err2204_t *error);

#endif
