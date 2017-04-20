#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include <math.h>

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

    sprintf(debugString, "CPU Started");
    debug(debugString, INFO);

    while(1)
    {
        /* Reading instruction at the address specified by PC */
        sprintf(debugString, "Reading instruction at 0x%" PRIx64, cpuDevice->PC);
        debug(debugString, INFO);
        result = memDirector(cpuDevice->PC, cpuDevice, ramDevice);
        switch (result)
        {
            case DEV_REG:
                sprintf(debugString, "Reading instruction from DEV_REG");
                debug(debugString, INFO);
                result = SUCCESS;
                cpuDevice->currentInstruction = cpuDevice->registers[cpuDevice->PC];
                break;
            case DEV_RAM:
                sprintf(debugString, "Reading instruction from DEV_RAM");
                debug(debugString, INFO);
                result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->currentInstruction);
                break;
            case DEV_NULL:
                sprintf(debugString, "Reading instruction from DEV_NULL");
                debug(debugString, WARNING);
                result = SUCCESS;
                cpuDevice->currentInstruction = (uint64_t) 0;
                break;
            case DEV_INVALID:
                sprintf(debugString, "Reading instruction from DEV_INVALID");
                debug(debugString, ERROR);
                result = ERR_READ_FROM_INVALID;
                break;
        }
        

        /* Did we fail to read the instruction? */
        if (result != SUCCESS)
        {
            sprintf(debugString, "Failed. Error %i", result);
            debug(debugString, ERROR);
            error.errnum = result;
            error.address = cpuDevice->PC;
            return(error);
        }
        
        sprintf(debugString, "Instruction: 0x%" PRIx64, cpuDevice->currentInstruction);
        debug(debugString, INFO);

        /* Decode instruction */
        switch(cpuDevice->currentInstruction)
        {
            case NOOP:
                sprintf(debugString, "Instruction: NOOP");
                debug(debugString, INFO);
                result = SUCCESS;
                cpuDevice->PC++;
                break;
                
            case STOP:
                sprintf(debugString, "Instruction: STOP");
                debug(debugString, INFO);
                error.errnum = SUCCESS;
                error.address = cpuDevice->PC;
                return (error);
                break;

            case COPY:
                sprintf(debugString, "Instruction: COPY");
                debug(debugString, INFO);
                error = copy2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case PRNT:
                sprintf(debugString, "Instruction: PRNT");
                debug(debugString, INFO);
                error = prnt2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case JUML:
                sprintf(debugString, "Instruction: JUML");
                debug(debugString, INFO);
                error = juml2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case STOR:
                sprintf(debugString, "Instruction: STOR");
                debug(debugString, INFO);
                error = stor2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case FREE:
                sprintf(debugString, "Instruction: FREE");
                debug(debugString, INFO);
                error = free2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case ADDA:
                sprintf(debugString, "Instruction: ADDA");
                debug(debugString, INFO);
                error = adda2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case SUBA:
                sprintf(debugString, "Instruction: SUBA");
                debug(debugString, INFO);
                error = suba2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case PRND:
                sprintf(debugString, "Instruction: PRND");
                debug(debugString, INFO);
                error = prnd2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case ORAD:
                sprintf(debugString, "Instruction: ORAD");
                debug(debugString, INFO);
                error = orad2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case ANDA:
                sprintf(debugString, "Instruction: ANDA");
                debug(debugString, INFO);
                error = anda2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case NOTA:
                sprintf(debugString, "Instruction: NOTA");
                debug(debugString, INFO);
                error = nota2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case NNDA:
                sprintf(debugString, "Instruction: NNDA");
                debug(debugString, INFO);
                error = nanda2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case NORA:
                sprintf(debugString, "Instruction: NORA");
                debug(debugString, INFO);
                error = nora2204(cpuDevice, ramDevice, debugString);
                if (error.errnum != SUCCESS)
                {
                    return (error);
                }
                break;
                
            case XORA:
                sprintf(debugString, "Instruction: XORA");
                debug(debugString, INFO);
                error = xora2204(cpuDevice, ramDevice, debugString);
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

err2204_t checkResult(int result, uint64_t address, char *debugString, const char *errorText)
{
    err2204_t error;
    error.errnum = result;
    error.address = address;
    if (result != SUCCESS)
    {
        #ifdef CPU_DEBUG
            sprintf(debugString, "%s (Error %i)", errorText, result);
            debug(debugString, ERROR);
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

void debug(char *string, int level)
{
    #ifdef CPU_DEBUG
        char verbosity[5];
        struct timespec spec = print_current_time_with_ms();
        long ms; // Milliseconds
        time_t s;  // Seconds
        
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
            s  = spec.tv_sec;
            ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
            printf("[%" PRIdMAX ".%03ld] [%s] %s\n", (intmax_t ) s, ms, verbosity, string);
        }
    #endif
    return;
}

/* http://stackoverflow.com/a/17371925 */
struct timespec print_current_time_with_ms(void)
{
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    
    return (spec);
}

int getArg(cpu_t *cpuDevice, ram_t *ramDevice, int argNumber, char *debugString)
{
    int sourceDevice;
    int result;
    
    sourceDevice = memDirector(cpuDevice->PC, cpuDevice, ramDevice);
    switch (sourceDevice)
    {
        case DEV_REG:
            sprintf(debugString, "Reading from DEV_REG");
            debug(debugString, INFO);
            result = SUCCESS;
            cpuDevice->arguments[argNumber] = cpuDevice->registers[cpuDevice->PC];
            break;
        case DEV_RAM:
            sprintf(debugString, "Reading from DEV_RAM");
            debug(debugString, INFO);
            result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->arguments[argNumber]);
            break;
        case DEV_NULL:
            sprintf(debugString, "Reading from DEV_NULL");
            debug(debugString, WARNING);
            result = SUCCESS;
            cpuDevice->arguments[argNumber] = (uint64_t) 0;
            break;
        case DEV_INVALID:
            sprintf(debugString, "Reading from DEV_INVALID");
            debug(debugString, ERROR);
            result = ERR_READ_FROM_INVALID;
            break;
        default:
            sprintf(debugString, "Reading from ???");
            debug(debugString, ERROR);
            result = ERR_UNEXPECTED_RESULT;
    }
    return (result);
}
