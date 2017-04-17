#include <stdint.h>
#include <stdlib.h>

#include "ram.h"

void ramInit(uint8_t ramAddress, uint64_t ramSize, FILE *bootloader,
            ram_t *ramDevice)
{
    ramDevice->address = ramAddress;
    ramDevice->size = ramSize;
    ramDevice->ram = (uint64_t*) malloc(sizeof(uint64_t) * ramSize);
    ramDevice->states = (uint8_t*) malloc(sizeof(uint8_t) * ramSize);
    return(NULL);
}

int ramRead(ram_t *ramDevice, uint64_t address, uint64_t *readTo)
{
    /* Check if the destination address isn't too high */
    if (address >= (ramDevice->address + ramDevice->size))
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    *readTo = ramDevice->ram[address - ramDevice->address];
    return(0);
}

int ramWrite(ram_t *ramDevice, uint64_t address, uint64_t data)
{
    /* Check if the destination address isn't too high */
    if (address >= (ramDevice->address + ramDevice->size))
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
        return(2);
    }
    
    ramDevice->ram[address - ramDevice->address] = data;
    ramDevice->states[address - ramDevice->address] = RAM_USED;
    return(0);
}

int ramFree(ram_t *ramDevice, uint64_t address)
{
    /* Check if the destination address isn't too high */
    if (address >= (ramDevice->address + ramDevice->size))
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    ramDevice->states[address - ramDevice->address] = RAM_FREE;
    return(0);
}

uint8_t ramState(ram_t *ramDevice, uint64_t address)
{
    /* Check if the destination address isn't too high */
    if (address >= (ramDevice->address + ramDevice->size))
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    /* Check if the destination address isn't too low */
    if (address < ramDevice->address)
    {
        return(ERR_ADDRESS_OUT_OF_RANGE);
    }
    
    return(ramDevice->states[address - ramDevice->address]);
}
