#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "ram.h"
#include "errors.h"
#include "./2204/2204.h"

int ramInit(ram_t *ramDevice, uint8_t ramAddress, uint64_t ramSize)
{
    uint64_t i;
    ramDevice->address = ramAddress;
    
    /* There must be at least 1 register, so the RAM can't start at address 1 */
    if (ramDevice->address < 2)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    ramDevice->size = ramSize;
    ramDevice->addressMax = ramAddress + ramSize - 1;
    printf("Max RAM address: 0x%" PRIx64 "\n", ramDevice->addressMax);
    if (ramDevice->addressMax > 0xFFFFFFFFFFFFFFFF)
    {
        /* It shouldn't be possible for this to ever happen */
        return(ERR_END_ADDRESS_OUT_OF_RANGE);
    }
    
    /* Allocate memory for the RAM */
    ramDevice->ram = (uint64_t*) malloc(sizeof(uint64_t) * ramSize);
    ramDevice->states = (uint8_t*) malloc(sizeof(uint8_t) * ramSize);
    
    /* Initialise all memory with the STOP instruction */
    /* Mark all RAM locations as FREE */
    for (i = 0; i < ramSize; i++)
    {
        ramDevice->ram[i] = STOP;
        ramDevice->states[i] = RAM_FREE;
    }
    
    return(SUCCESS);
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
    if (ramAddress > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (ramAddress < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the given address range is valid */
    if ((ramAddress + length - 1) > ramDevice->addressMax)
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
        return(ERR_ADDRESS_TOO_HIGH);
    }

    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_TOO_LOW);
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
    if (ramAddress > ramDevice->addressMax)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address isn't too low */
    if (ramAddress < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the given address range is valid */
    if ((ramAddress + length - 1) > ramDevice->addressMax)
    {
        return(ERR_END_ADDRESS_OUT_OF_RANGE);
    }

    /* Check if the destination address range is in use */
    for (i = 0; i < length; i++)
    {
        if (ramDevice->states[ramAddress - ramDevice->address + i] == RAM_USED)
        {
            return(ERR_RAM_ADDRESS_IN_USE);
        }
    }
    
    /* Mark writted addresses as in use */
    for (i = 0; i < length; i++)
    {
        ramDevice->states[ramAddress - ramDevice->address + i] = RAM_USED;
    }

    memcpy(&(ramDevice->ram[ramAddress - ramDevice->address]), writeFrom, length);
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
