#include <time.h>
#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t stor2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
    int destinationDevice;
    err2204_t error;

    /* Get destination address */
    cpuDevice->PC++;
    sprintf(debugString, "Getting destination address.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 0, debugString); /* Put destination in arg register 0 */
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }

    /* Get destination device */
    sprintf(debugString, "Getting destination device.");
    debug(debugString, INFO);
    destinationDevice = memDirector(cpuDevice->arguments[0], cpuDevice, ramDevice);
    sprintf(debugString, "Destination device: %i", destinationDevice);
    debug(debugString, INFO);

    /* Get data */
    cpuDevice->PC++;
    sprintf(debugString, "Getting data.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 1, debugString); /* Put destination in arg register 0 */
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    
    sprintf(debugString, "Data: %" PRIx64, cpuDevice->arguments[1]);
    debug(debugString, INFO);

    /* Write data */
    sprintf(debugString, "Writing data.");
    debug(debugString, INFO);
    switch (destinationDevice)
    {
        case DEV_REG:
            sprintf(debugString, "Writing data to DEV_REG");
            debug(debugString, INFO);
            result = SUCCESS;
            cpuDevice->registers[cpuDevice->arguments[0]] = cpuDevice->arguments[1];
            break;
        case DEV_RAM:
            sprintf(debugString, "Writing data to DEV_RAM");
            debug(debugString, INFO);
            result = ramWrite(ramDevice, cpuDevice->arguments[0], cpuDevice->arguments[1]);
            error = checkResult(result, cpuDevice->PC, debugString, "Failed to write to RAM.");
            if (result != SUCCESS)
            {
                return (error);
            }
            break;
        case DEV_NULL:
            sprintf(debugString, "Writing data to DEV_NULL");
            debug(debugString, WARNING);
            result = SUCCESS;
            break;
        default:
            sprintf(debugString, "Writing data to ???");
            debug(debugString, WARNING);
            result = ERR_UNEXPECTED_RESULT;
            error = checkResult(result, cpuDevice->PC, debugString, "Unexpected destination device.");
            return (error);
            break;
    }

    sprintf(debugString, "Success.");
    debug(debugString, INFO);
    cpuDevice->PC++;
    return (error);
}
