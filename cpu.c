#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#include "cpu.h"
#include "errors.h"
#include "./2204/2204.h"

void cpuInit(cpu_t *cpuDevice, uint64_t bootAddress, uint64_t registerCount)
{
    cpuDevice->PC = bootAddress;
    cpuDevice->registers = (uint64_t*) malloc(sizeof(uint64_t) * registerCount);
    cpuDevice->registerMax = registerCount;
    return;
}

err2204_t cpuRun(cpu_t *cpuDevice, ram_t *ramDevice)
{
    err2204_t error;
    char debugString[128];
    int result;
    time_t startTime = time(NULL);

    sprintf(debugString, "CPU Started");
    debug(debugString, startTime, INFO);

    while(1)
    {
        /* Reading instruction at the address specified by PC */
        sprintf(debugString, "Reading instruction at %" PRIx64, cpuDevice->PC);
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
        
        sprintf(debugString, "Instruction: %" PRIx64, cpuDevice->currentInstruction);
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
                
            case STOP:
                sprintf(debugString, "Instruction: STOP");
                debug(debugString, startTime, INFO);
                error.errnum = SUCCESS;
                error.address = cpuDevice->PC;
                return (error);
                break;

            case COPY:
                sprintf(debugString, "Instruction: COPY");
                debug(debugString, startTime, INFO);
                error = copy2204(cpuDevice, ramDevice, debugString, &startTime);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case PRNT:
                sprintf(debugString, "Instruction: PRNT");
                debug(debugString, startTime, INFO);
                error = prnt2204(cpuDevice, ramDevice, debugString, &startTime);
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
    error.errnum = ERR_CPU_BREAK;
    error.address = cpuDevice->PC;
    return (error);
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
    return (error);
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
    #ifdef CPU_DEBUG
        char verbosity[5];
        
        switch (level)
        {
            case INFO:
                strcpy(verbosity, "INFO");
                break;
            case WARNING:
                strcpy(verbosity, "WARNING");
                break;
            case ERROR:
                strcpy(verbosity, "ERROR");
                break;
        }
        
        if (level <= CPU_DEBUG)
        {
            double seconds;

            time_t currentTime = time(NULL);
            seconds = difftime(currentTime, startTime);
            printf("[%f] [%s] %s\n", seconds, verbosity, string);
        }
    #endif
    return;
}
