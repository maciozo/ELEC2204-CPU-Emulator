#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t prnt2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString, time_t *startTime)
{
    int result;
    int sourceDevice;
    uint64_t data;
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
    
    switch (sourceDevice)
    {
        case DEV_NULL:
            sprintf(debugString, "Printing from DEV_NULL.");
            debug(debugString, *startTime, INFO);
            printf("%" PRIx64 "\n", (uint64_t) 0);
            break;
        case DEV_REG:
            sprintf(debugString, "Printing from DEV_REG address %" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, *startTime, INFO);
            printf("%" PRIx64 "\n", cpuDevice->registers[cpuDevice->arguments[0]]);
            break;
        case DEV_RAM:
            sprintf(debugString, "Printing from DEV_RAM address %" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, *startTime, INFO);
            result = ramRead(ramDevice, cpuDevice->arguments[0], &data);
            error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.", *startTime);
            if (result != SUCCESS)
            {
                return (error);
            }
            printf("%" PRIx64 "\n", data);
            break;
        default:
            sprintf(debugString, "Printing from ??? address %" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, *startTime, WARNING);
            result = ERR_UNEXPECTED_RESULT;
            error = checkResult(result, cpuDevice->PC, debugString, "Unknown source device.", *startTime);
            return (error);
            break;
    }
    sprintf(debugString, "Success.");
    debug(debugString, *startTime, INFO);
    cpuDevice->PC++;
    return (error);
}
