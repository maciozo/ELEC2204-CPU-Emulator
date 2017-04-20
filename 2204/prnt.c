#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t prnt2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
    int sourceDevice;
    uint64_t data;
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
    
    switch (sourceDevice)
    {
        case DEV_NULL:
            sprintf(debugString, "Printing from DEV_NULL.");
            debug(debugString, INFO);
            printf("%" PRIx64 "\n", (uint64_t) 0);
            break;
        case DEV_REG:
            sprintf(debugString, "Printing from DEV_REG address %" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, INFO);
            printf("%" PRIx64 "\n", cpuDevice->registers[cpuDevice->arguments[0]]);
            break;
        case DEV_RAM:
            sprintf(debugString, "Printing from DEV_RAM address %" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, INFO);
            result = ramRead(ramDevice, cpuDevice->arguments[0], &data);
            error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.");
            if (result != SUCCESS)
            {
                return (error);
            }
            printf("%" PRIx64 "\n", data);
            break;
        default:
            sprintf(debugString, "Printing from ??? address %" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, WARNING);
            result = ERR_UNEXPECTED_RESULT;
            error = checkResult(result, cpuDevice->PC, debugString, "Unknown source device.");
            return (error);
            break;
    }
    sprintf(debugString, "Success.");
    debug(debugString, INFO);
    cpuDevice->PC++;
    return (error);
}
