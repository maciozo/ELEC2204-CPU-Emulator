#include <inttypes.h>

#include "2204.h"
#include "../errors.h"
#include "../cpu.h"
#include "../ram.h"

err2204_t juml2204(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    int result;
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
    
    /* Set programme counter to new address */
    sprintf(debugString, "Jumping to address %" PRIx64 "\n", cpuDevice->arguments[0]);
    debug(debugString, INFO);
    cpuDevice->PC = cpuDevice->arguments[0];
    return (error);
}
