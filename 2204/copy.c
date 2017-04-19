#include <time.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t copy2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString, time_t *startTime)
{
    int result;
    int sourceDevice;
    int destinationDevice;
    err2204_t error;
    
    /* Get source address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting source address.");
    debug(debugString, *startTime, INFO);
    result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[0]);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", *startTime);
    if (result != SUCCESS)
    {
        return (error);
    }
    sourceDevice = memDirector(cpuDevice->arguments[0], cpuDevice, ramDevice);
    sprintf(debugString, "Source device: %i", sourceDevice);
    debug(debugString, *startTime, INFO);
    
    /* Get destination address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting destination address.");
    debug(debugString, *startTime, INFO);
    result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[1]);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", *startTime);
    if (result != SUCCESS)
    {
        return (error);
    }
    destinationDevice = memDirector(cpuDevice->arguments[1], cpuDevice, ramDevice);
    sprintf(debugString, "Destination device: %i", destinationDevice);
    debug(debugString, *startTime, INFO);
    
    /* Check to make sure the copy is legal. i.e. (Device -> Register) or (Register -> Device) */
    sprintf(debugString, "Verifying copy operation.");
    debug(debugString, *startTime, INFO);
    result = legalCopy(sourceDevice, destinationDevice);
    error = checkResult(result, cpuDevice->PC, debugString, "Illegal copy operation.", *startTime);
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
                    debug(debugString, *startTime, INFO);
                    break;
                case DEV_REG:
                    sprintf(debugString, "Null -> Register");
                    debug(debugString, *startTime, INFO);
                    cpuDevice->registers[cpuDevice->arguments[1]] = 0x0000000000000000;
                    break;
                case DEV_RAM:
                    sprintf(debugString, "Null -> RAM");
                    debug(debugString, *startTime, INFO);
                    result = ramWrite(ramDevice, cpuDevice->arguments[1], 0x0000000000000000);
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.", *startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    sprintf(debugString, "Null -> ???");
                    debug(debugString, *startTime, INFO);
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.", *startTime);
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
                    debug(debugString, *startTime, INFO);
                    break;
                case DEV_REG:
                    sprintf(debugString, "Register -> Register");
                    debug(debugString, *startTime, INFO);
                    cpuDevice->registers[cpuDevice->arguments[1]] = cpuDevice->registers[cpuDevice->arguments[0]];
                    break;
                case DEV_RAM:
                    sprintf(debugString, "Register -> RAM");
                    debug(debugString, *startTime, INFO);
                    result = ramWrite(ramDevice, cpuDevice->arguments[1], cpuDevice->registers[cpuDevice->arguments[0]]);
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.", *startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    sprintf(debugString, "Register -> ???");
                    debug(debugString, *startTime, WARNING);
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.", *startTime);
                    return (error);
                    break;
            }
            break;
        
        case DEV_RAM:
            switch (destinationDevice)
            {
                case DEV_NULL:
                    sprintf(debugString, "RAM -> Null");
                    debug(debugString, *startTime, INFO);
                    break;
                case DEV_REG:
                    sprintf(debugString, "RAM -> Register");
                    debug(debugString, *startTime, INFO);
                    result = ramRead(ramDevice, cpuDevice->arguments[0], &(cpuDevice->registers[cpuDevice->arguments[1]]));
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", *startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    sprintf(debugString, "RAM -> ???");
                    debug(debugString, *startTime, WARNING);
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.", *startTime);
                    return (error);
                    break;
            }
            break;
            
        default:
            sprintf(debugString, "??? ->");
            debug(debugString, *startTime, WARNING);
            result = ERR_UNEXPECTED_RESULT;
            error = checkResult(result, cpuDevice->PC, debugString, "Unexpected source device.", *startTime);
            return (error);
            break;
    }
    sprintf(debugString, "Success.");
    debug(debugString, *startTime, INFO);
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
