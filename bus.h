#include <stdint.h>

typedef struct
{
    /* The raw data that is stored on the bus */
    uint64_t data;
    
    /* The address of the device that was last given permission to write */
    uint64_t writingAddress;
    
    /* Whether a device is writing to the bus */
    uint8_t inUse;
    
    /* 
        The address of the device for which the data is headed
        Other devices may read from the bus as well.
    */
    uint8_t targetAddress;
} bus_t;

/* 
    Returns the current value stored on the bus.
*/
uint64_t busRead(bus_t* bus)

/*
    Writes data to the bus.
    Returns 0 if no write permissions have been given.
    Returns the address of device that currently has write permission.
        If the returned address is the same as sourceAddress, then the write 
        operation succeeded. Otherwise, the bus is in use by another device with
        the returned address.
*/
int busWrite(bus_t* bus, uin64_t* sourceAddress, uint64_t* data);

/*
    Opens the bus for writing.
    Returns the address of device that currently has write permission.
        If the returned address is the same as sourceAddress, then the write 
        operation succeeded. Otherwise, the bus is in use by another device with
        the returned address.
*/
int busOpen(bus_t* bus, uin64_t* sourceAddress);

/*
    Closes the bus, allowing another device to open it.
    Returns 0 if the bus is already closed.
    Returns the address of device that currently has write permission.
        If the returned address is the same as sourceAddress, then the write 
        operation succeeded. Otherwise, the bus is in use by another device with
        the returned address.
*/
int busClose(bus_t* bus, uin64_t* sourceAddress);
