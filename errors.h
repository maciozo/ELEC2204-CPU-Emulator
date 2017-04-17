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

typedef struct
{
    int errno;
    uint64_t address;
} err2204_t;

#endif
