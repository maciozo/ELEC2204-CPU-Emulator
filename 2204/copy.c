#include <time.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t copy2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
    int sourceDevice;
    int destinationDevice;
    err2204_t error;
    
    /* Get source address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting source address.");
    debug(debugString, INFO);
    sourceDevice = memDirector(cpuDevice->PC, cpuDevice, ramDevice);
    switch (sourceDevice)
    {
        case DEV_REG:
            sprintf(debugString, "Reading address from DEV_REG");
            debug(debugString, INFO);
            result = SUCCESS;
            cpuDevice->arguments[0] = cpuDevice->registers[cpuDevice->PC];
            break;
        case DEV_RAM:
            sprintf(debugString, "Reading address from DEV_RAM");
            debug(debugString, INFO);
            result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[0]);
            break;
        case DEV_NULL:
            sprintf(debugString, "Reading address from DEV_NULL");
            debug(debugString, WARNING);
            result = SUCCESS;
            cpuDevice->arguments[0] = (uint64_t) 0;
            break;
        case DEV_INVALID:
            sprintf(debugString, "Reading address from DEV_INVALID");
            debug(debugString, ERROR);
            result = ERR_READ_FROM_INVALID;
            break;
    }
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    sourceDevice = memDirector(cpuDevice->arguments[0], cpuDevice, ramDevice);
    sprintf(debugString, "Source device: %i", sourceDevice);
    debug(debugString, INFO);
    
    /* Get destination address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting destination address.");
    debug(debugString, INFO);
    sourceDevice = memDirector(cpuDevice->PC, cpuDevice, ramDevice);
    switch (sourceDevice)
    {
        case DEV_REG:
            sprintf(debugString, "Reading address from DEV_REG");
            debug(debugString, INFO);
            result = SUCCESS;
            cpuDevice->arguments[1] = cpuDevice->registers[cpuDevice->PC];
            break;
        case DEV_RAM:
            sprintf(debugString, "Reading address from DEV_RAM");
            debug(debugString, INFO);
            result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[1]);
            break;
        case DEV_NULL:
            sprintf(debugString, "Reading address from DEV_NULL");
            debug(debugString, WARNING);
            result = SUCCESS;
            cpuDevice->arguments[1] = (uint64_t) 0;
            break;
        case DEV_INVALID:
            sprintf(debugString, "Reading address from DEV_INVALID");
            debug(debugString, ERROR);
            result = ERR_READ_FROM_INVALID;
            break;
    }
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    destinationDevice = memDirector(cpuDevice->arguments[1], cpuDevice, ramDevice);
    sprintf(debugString, "Destination device: %i", destinationDevice);
    debug(debugString, INFO);
    
    /* Check to make sure the copy is legal. i.e. (Device -> Register) or (Register -> Device) */
    sprintf(debugString, "Verifying copy operation.");
    debug(debugString, INFO);
    result = legalCopy(sourceDevice, destinationDevice);
    error = checkResult(result, cpuDevice->PC, debugString, "Illegal copy operation.");
    if (result != SUCCESS)
    {
        return (error);
    }
    
    
    switch (sourceDevice)
    {
        case DEV_NULL:
            switch (destinationDevice)
            {
                case DEV_NULL:
                    sprintf(debugString, "Null -> Null");
                    debug(debugString, INFO);
                    break;
                case DEV_REG:
                    sprintf(debugString, "Null -> Register");
                    debug(debugString, INFO);
                    cpuDevice->registers[cpuDevice->arguments[1]] = 0x0000000000000000;
                    break;
                case DEV_RAM:
                    sprintf(debugString, "Null -> RAM");
                    debug(debugString, INFO);
                    result = ramWrite(ramDevice, cpuDevice->arguments[1], 0x0000000000000000);
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.");
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    sprintf(debugString, "Null -> ???");
                    debug(debugString, INFO);
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.");
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
            }
            break;
            
        case DEV_REG:
            switch (destinationDevice)
            {
                case DEV_NULL:
                    sprintf(debugString, "Register -> Null");
                    debug(debugString, INFO);
                    break;
                case DEV_REG:
                    sprintf(debugString, "Register -> Register");
                    debug(debugString, INFO);
                    cpuDevice->registers[cpuDevice->arguments[1]] = cpuDevice->registers[cpuDevice->arguments[0]];
                    break;
                case DEV_RAM:
                    sprintf(debugString, "Register -> RAM");
                    debug(debugString, INFO);
                    result = ramWrite(ramDevice, cpuDevice->arguments[1], cpuDevice->registers[cpuDevice->arguments[0]]);
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.");
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    sprintf(debugString, "Register -> ???");
                    debug(debugString, WARNING);
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.");
                    return (error);
                    break;
            }
            break;
        
        case DEV_RAM:
            switch (destinationDevice)
            {
                case DEV_NULL:
                    sprintf(debugString, "RAM -> Null");
                    debug(debugString, INFO);
                    break;
                case DEV_REG:
                    sprintf(debugString, "RAM -> Register");
                    debug(debugString, INFO);
                    result = ramRead(ramDevice, cpuDevice->arguments[0], &(cpuDevice->registers[cpuDevice->arguments[1]]));
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.");
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    sprintf(debugString, "RAM -> ???");
                    debug(debugString, WARNING);
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.");
                    return (error);
                    break;
            }
            break;
            
        default:
            sprintf(debugString, "??? ->");
            debug(debugString, WARNING);
            result = ERR_UNEXPECTED_RESULT;
            error = checkResult(result, cpuDevice->PC, debugString, "Unexpected source device.");
            return (error);
            break;
    }
    sprintf(debugString, "Success.");
    debug(debugString, INFO);
    cpuDevice->PC++;
    return (error);
}

int legalCopy(int sourceDev, int destinationDev)
{
    /* Any copy to or from an invalid device is invalid */
    if (sourceDev == DEV_INVALID)
    {
        return (ERR_READ_FROM_INVALID);
    }
    if (destinationDev == DEV_INVALID)
    {
        return (ERR_COPY_TO_INVALID);
    }
    
    /* Any copy operations to or from a register are fine */
    if ((sourceDev == DEV_REG) | (destinationDev == DEV_REG))
    {
        return (SUCCESS);
    }
    
    /* Any copy operations to or from the null device are fine */
    if ((sourceDev == DEV_NULL) | (destinationDev == DEV_NULL))
    {
        return (SUCCESS);
    }
    
    /* Any other copy (Device <-> Device) is illegal */
    return (ERR_ILLEGAL_MEMORY_COPY);
}
