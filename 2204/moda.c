#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t moda2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
    int destinationDevice;
    int sourceDevice;
    err2204_t error;
    
    /* Get first operand address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting first operand address");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 0, debugString);
    
    /* Checking if the first operand is in the CPU registers */
    sourceDevice = memDirector(cpuDevice->arguments[0], cpuDevice, ramDevice);
    if (sourceDevice != DEV_REG)
    {
        sprintf(debugString, "Operand not in DEV_REG.");
        debug(debugString, ERROR);
        result = ERR_READ_FROM_INVALID;
    }
    else
    {
        result = SUCCESS;
    }
    error = checkResult(result, cpuDevice->PC, debugString, "First operand not in DEV_REG.");
    if (result != SUCCESS)
    {
        return (error);
    }
    sprintf(debugString, "First operand at address 0x%" PRIx64, cpuDevice->arguments[0]);
    debug(debugString, INFO);
    
    /* Get first operand */
    cpuDevice->arguments[0] = cpuDevice->registers[cpuDevice->arguments[0]];
    sprintf(debugString, "First operand 0x%" PRIx64, cpuDevice->arguments[0]);
    debug(debugString, INFO);
    
    /* Get second operand address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting second operand address.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 1, debugString);
    
    /* Checking if the second operand is in the CPU registers */
    sourceDevice = memDirector(cpuDevice->arguments[1], cpuDevice, ramDevice);
    if (sourceDevice != DEV_REG)
    {
        sprintf(debugString, "Operand not in DEV_REG.");
        debug(debugString, ERROR);
        result = ERR_READ_FROM_INVALID;
    }
    else
    {
        result = SUCCESS;
    }
    error = checkResult(result, cpuDevice->PC, debugString, "Second operand not in DEV_REG.");
    if (result != SUCCESS)
    {
        return (error);
    }
    sprintf(debugString, "Second operand at address 0x%" PRIx64, cpuDevice->arguments[1]);
    debug(debugString, INFO);
    
    /* Get second operand */
    cpuDevice->arguments[1] = cpuDevice->registers[cpuDevice->arguments[1]];
    sprintf(debugString, "Second operand 0x%" PRIx64, cpuDevice->arguments[1]);
    debug(debugString, INFO);
    
    /* Get writeback address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting writeback address.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 2, debugString);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    sprintf(debugString, "Writeback at address 0x%" PRIx64, cpuDevice->arguments[2]);
    debug(debugString, INFO);
    
    /* Get writeback device */
    destinationDevice = memDirector(cpuDevice->arguments[2], cpuDevice, ramDevice);
    switch (destinationDevice)
    {
        case DEV_NULL:
            sprintf(debugString, "Writeback to DEV_NULL.");
            debug(debugString, WARNING);
            result = SUCCESS;
            break;
        case DEV_REG:
            sprintf(debugString, "Writeback to DEV_REG.");
            debug(debugString, INFO);
            cpuDevice->registers[cpuDevice->arguments[2]] = cpuDevice->arguments[0] % cpuDevice->arguments[1];
            result = SUCCESS;
            break;
        case DEV_RAM:
            sprintf(debugString, "Writeback to DEV_RAM.");
            debug(debugString, INFO);
            result = ramWrite(ramDevice, cpuDevice->arguments[2], cpuDevice->arguments[0] % cpuDevice->arguments[1]);
            break;
        default:
            sprintf(debugString, "Writeback to ???.");
            debug(debugString, INFO);
            result = ERR_UNEXPECTED_RESULT;
            break;
    }
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    
    cpuDevice->PC++;
    return (error);
}
