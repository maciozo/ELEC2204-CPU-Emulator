#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t free2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
    int destinationDevice;
    err2204_t error;
    
    /* Get address to be cleared */
    cpuDevice->PC++;
    sprintf(debugString, "Getting address to be cleared.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 0, debugString);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    
    /* Check if we're actually freeing a RAM address */
    destinationDevice = memDirector(cpuDevice->registers[0], cpuDevice, ramDevice);
    if (destinationDevice != DEV_RAM)
    {
        sprintf(debugString, "Attempt to free non-RAM address.");
        debug(debugString, WARNING);
        return (error);
    }
    
    /* Get length to clear */
    cpuDevice->PC++;
    sprintf(debugString, "Getting length to clear.");
    debug(debugString, INFO);
    result = getArg(cpuDevice, ramDevice, 1, debugString);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    
    /* Free the memory address */
    sprintf(debugString, "Freeing address %" PRIx64 " to %" PRIx64 "\n", cpuDevice->arguments[0], cpuDevice->arguments[0] + cpuDevice->arguments[1]);
    result = ramFree(ramDevice, cpuDevice->arguments[0], cpuDevice->arguments[1]);
    error = checkResult(result, cpuDevice->PC, debugString, "Failed to read from device.");
    if (result != SUCCESS)
    {
        return (error);
    }
    
    debug(debugString, INFO);
    cpuDevice->PC++;
    return (error);
}
