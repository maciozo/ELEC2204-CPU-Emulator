#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ram.h"

void ramInit(uint8_t ramAddress, uint64_t ramSize, ram_t *ramDevice)
{
    ramDevice->address = ramAddress;
    ramDevice->size = ramSize;
    ramDevice->ram = (uint64_t*) malloc(sizeof(uint64_t) * ramSize);
    ramDevice->states = (uint8_t*) malloc(sizeof(uint8_t) * ramSize);
    ramDevice->addressMax = ramAddress + size - 1;
    return(NULL);
}

int ramRead(ram_t *ramDevice, uint64_t address, uint64_t *readTo)
{
    /* Check if the destination address isn't too high */
    if (address > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    *readTo = ramDevice->ram[address - ramDevice->address];
    return(SUCCESS);
}

int ramReadBurst(ram_t *ramDevice, uint64_t ramAddress, uint64_t *readTo, uint64_t length)
{
    /* Check if the destination address isn't too high */
    if (address > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the given address range is valid */
    if ((address + length - 1) > ramDevice->addressMax)
    {
        return(ERR_END_ADDRESS_OUT_OF_RANGE);
    }

    memcpy(readTo, &(ramDevice->ram[ramAddress]), length);
    return(SUCCESS);
}

int ramWrite(ram_t *ramDevice, uint64_t address, uint64_t data)
{
    /* Check if the destination address isn't too high */
    if (address > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address is in use */
    if (ramDevice->states[address - ramDevice->address] == RAM_USED)
    {
        return(ERR_RAM_ADDRESS_IN_USE);
    }

    ramDevice->ram[address - ramDevice->address] = data;
    ramDevice->states[address - ramDevice->address] = RAM_USED;
    return(SUCCESS);
}

int ramWriteBurst(ram_t *ramDevice, uint64_t ramAddress, uint64_t *writeFrom, uint64_t length)
{
    uint64_t i;

    /* Check if the destination address isn't too high */
    if (address > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the given address range is valid */
    if ((address + length - 1) > ramDevice->addressMax)
    {
        return(ERR_END_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address range is in use */
    for (i = 0; i < length; i++)
    {
        if (ramDevice->states[address - ramDevice->address + i] == RAM_USED)
        {
            return(ERR_RAM_ADDRESS_IN_USE);
        }
    }
    
    /* Mark writted addresses as in use */
    for (i = 0; i < length; i++)
    {
        ramDevice->states[address - ramDevice->address + i] = RAM_USED;
    }

    memcpy(&(ramDevice->ram[address - ramDevice->address]), writeFrom, length);
    return(SUCCESS);
}

int ramFree(ram_t *ramDevice, uint64_t address, uint64_t length)
{
    uint64_t i;

    /* Check if the destination address isn't too high */
    if (address > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the given address range is valid */
    if ((address + length - 1) > ramDevice->addressMax)
    {
        return(ERR_END_ADDRESS_OUT_OF_RANGE);
    }

    for (i = 0; i < length; i++)
    {
        ramDevice->states[address - ramDevice->address + i] = RAM_FREE;
    }
    return(SUCCESS);
}

int ramState(ram_t *ramDevice, uint64_t address, uint64_t length)
{
    uint64_t i;

    /* Check if the destination address isn't too high */
    if (address > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the given address range is valid */
    if ((address + length - 1) > ramDevice->addressMax)
    {
        return(ERR_END_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address range is in use */
    for (i = 0; i < length; i++)
    {
        if (ramDevice->states[address - ramDevice->address + i] == RAM_USED)
        {
            return(RAM_USED);
        }
    }

    return(RAM_FREE);
}
