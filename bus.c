#include <stdint.h>
#include "bus.h"

int busInit(bus_t* bus)
{
    bus->data = 0;
    bus->inUse = 0;
    bus->writingAddress = 0;
    return 0;
}

uint64_t busRead(bus_t* bus)
{
    return bus->data;
}

uint64_t busWrite(bus_t* bus, uin64_t* sourceAddress, uint64_t* data)
{
    if (!(bus->inUse))
    {
        /* No write permissions to the bus have been issued */
        return 0;
    }
    
    if (bus->writingAddress != *sourceAddress)
    {
        /* The bus is in use by another device */
        return bus->writingAddress;
    }
    
    bus->data = *data;
    return *sourceAddress;
}

uint64_t busOpen(bus_t* bus, uin64_t* sourceAddress)
{
    if (bus->inUse)
    {
        /* The bus is already in use by another address */
        return bus->writingAddress;
    }
    
    bus->writingAddress = *sourceAddress;
    bus->inUse = 1;
    return *sourceAddress;
}

uint64_t busClose(bus_t* bus, uin64_t* sourceAddress)
{
    if (!(bus->inUse))
    {
        /* The bus has not been opened */
        return 0;
    }
    
    if (bus->writingAddress != *sourceAddress)
    {
        /* The bus is in use by another device */
        return bus->writingAddress;
    }
    
    bus->inUse = 0;
    return *sourceAddress;
}
