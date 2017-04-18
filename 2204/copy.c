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
    result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[0]);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", startTime);
    if (result != SUCCESS)
    {
        return (error);
    }
    sourceDevice = memDirector(cpuDevice->arguments[0], cpuDevice, ramDevice);
    
    /* Get destination address */
    cpuDevice->PC++;
    result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[1]);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", startTime);
    if (result != SUCCESS)
    {
        return (error);
    }
    destinationDevice = memDirector(cpuDevice->arguments[1], cpuDevice, ramDevice);
    
    /* Check to make sure the copy is legal. i.e. (Device -> Register) or (Register -> Device) */
    result = legalCopy(sourceDevice, deistinationDevice);
    error = checkResult(result, cpuDevice->PC, debugString, "Illegal copy operation.", startTime);
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
                    break;
                case DEV_REG:
                    cpuDevice->registers[cpuDevice->arguments[1]] = 0x0000000000000000;
                    break;
                case DEV_RAM:
                    result = ramWrite(ramDevice, cpuDevice->arguments[1], 0x0000000000000000);
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.", startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.", startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
            }
            
        case DEV_REG:
            switch (destinationDevice)
            {
                case DEV_NULL:
                    break;
                case DEV_REG:
                    cpuDevice->registers[cpuDevice->arguments[1]] = cpuDevice->registers[cpuDevice->arguments[0]];
                    break;
                case DEV_RAM:
                    result = ramWrite(ramDevice, cpuDevice->arguments[1], cpuDevice->registers[cpuDevice->arguments[0]]);
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.", startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                default:
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.", startTime);
                    return (error);
                    break;
            }
        
        case DEV_RAM:
            switch (destinationDevice)
            {
                case DEV_NULL:
                    break;
                case DEV_REG:
                    result = ramRead(ramDevice, cpuDevice->arguments[0], &(cpuDevice->registers[cpuDevice->arguments[1]]));
                    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", startTime);
                    if (result != SUCCESS)
                    {
                        return (error);
                    }
                    break;
                default:
                    result = ERR_UNEXPECTED_RESULT;
                    error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.", startTime);
                    return (error);
                    break;
            }
            
        default:
            result = ERR_UNEXPECTED_RESULT;
            error = checkResult(result, cpuDevice->PC, debugString, "Unexpected source device.", startTime);
            return (error);
            break;
    }
    
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
