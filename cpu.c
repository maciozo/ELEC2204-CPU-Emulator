#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"
#include "errors.h"
#include "./2204/2204.h"

#ifdef DEBUG
    #include <time.h>
#endif

void cpuInit(cpu_t *cpuDevice, uint64_t bootAddress, uint64_t registerCount)
{
    cpuDevice->PC = bootAddress;
    cpuDevice-registers = (uint64_t*) malloc(sizeof(uint64_t) * registerCount);
    cpuDevice->registerMax = registerCount;

    return(NULL);
}

err2204_t cpuRun(cpu_t *cpuDevice, ram_t *ramDevice)
{
    err2204_t error;
    char debugString[128];
    int result;
    int sourceDevice;
    int destinationDevice;

    #ifdef DEBUG
        time_t startTime = time(NULL);
        debugString = "CPU Started";
        debug(debugString, startTime, INFO);
    #endif


    while(1)
    {
        /* Reading instruction at the address specified by PC */
        sprintf(debugString, "Reading instruction at %x", cpuDevice->PC);
        debug(debugString, startTime, INFO);
        result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->currentInstruction);

        /* Did we fail to read the instruction? */
        if (result != SUCCESS)
        {
            sprintf(debugString, "Failed. Error %i", result);
            debug(debugString, startTime, ERROR);
            error.errnum = result;
            error.address = cpuDevice->PC;
            return(error);
        }
        
        sprintf(debugString, "Instruction: %x", cpuDevice->currentInstruction);
        debug(debugString, startTime, INFO);

        /* Decode instruction */
        switch(cpuDevice->currentInstruction)
        {
            case NOOP:
                sprintf(debugString, "Instruction: NOOP");
                debug(debugString, startTime, INFO);
                result = SUCCESS;
                cpuDevice->PC++;
                break;

            case COPY:
                sprintf(debugString, "Instruction: COPY");
                debug(debugString, startTime, INFO);
                error = copy2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            default:
                error.errnum = ERR_UNKNOWN_INSTRUCTION;
                error.address = cpuDevice->PC;
                return(error);
                break;
        }

    }
    return(NULL);
}

err2204_t checkResult(int result, uint64_t address, char *debugString, const char *errorText, time_t startTime)
{
    err2204_t error;
    error.errnum = result;
    error.address = address;
    if (result != SUCCESS)
    {
        #ifdef DEBUG
            sprintf(debugString, "%s (Error %i)", errorText, result);
            debug(debugString, startTime, ERROR);
        #endif
    }
    return (error)
}

int memDirector(uint64_t address, cpu_t *cpuDevice, ram_t *ramDevice)
{
    if (address > 0xFFFFFFFFFFFFFFFF)
    {
        return(DEV_INVALID);
    }

    if (address == 0)
    {
        return(DEV_NULL);
    }

    if (address <= cpuDevice->registerMax)
    {
        return(DEV_REG);
    }

    if ((address >= ramDevice->address) & (address <= ramDevice->addressMax))
    {
        return(DEV_RAM);
    }

    return(DEV_INVALID);
}

void debug(char *string, time_t startTime, int level)
{
    #ifdef DEBUG
        if (level <= CPU_DEBUG)
        {
            double seconds;

            time_t currentTime = time(NULL);
            seconds = difftime(currentTime, startTime);
            printf("[%f] %s\n", seconds, string);
        }
    #endif
    return(NULL);
}
