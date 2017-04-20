#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t prnd2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
    int sourceDevice;
    uint64_t data;
    err2204_t error;
    
    /* Get source address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting source address.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 0, debugString);
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
            debug(debugString, WARNING);
            printf("%" PRIu64 "\n", (uint64_t) 0);
            break;
        case DEV_REG:
            sprintf(debugString, "Printing from DEV_REG address 0x%" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, INFO);
            printf("%" PRIu64 "\n", cpuDevice->registers[cpuDevice->arguments[0]]);
            break;
        case DEV_RAM:
            sprintf(debugString, "Printing from DEV_RAM address 0x%" PRIx64 ".", cpuDevice->arguments[0]);
            debug(debugString, INFO);
            result = ramRead(ramDevice, cpuDevice->arguments[0], &data);
            error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from RAM.");
            if (result != SUCCESS)
            {
                return (error);
            }
            printf("%" PRIu64 "\n", data);
            break;
        default:
            sprintf(debugString, "Printing from ??? address 0x%" PRIx64 ".", cpuDevice->arguments[0]);
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
