#include <stdio.h>
#include <stdint.h>

#include "cpu.h"
#include "errors.h"

#ifdef DEBUG
    #include <time.h>
#endif

void cpuInit(uint64_t ramAddress)
{
    cpu_t cpuInfo;
    
    cpuInfo.ramAddress = ramAddress;
    cpuInfo.PC = ramAddress;
    
    return(NULL);
}

err2204_t cpuRun(cpu_t *cpuDevice, ram_t *ramDevice)
{
    uint8_t currentInstruction;
    uint64_t currentWord;
    uint64_t sourceAddress;
    err2204_t error;
    char debugString[128];
    int result;
    
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
        result = ramRead(ramDevice, cpuDevice->PC, &currentWord);
        
        /* Did we fail to read the instruction? */
        if (result != SUCCESS)
        {
            sprintf(debugString, "Failed. Error %i", result);
            debug(debugString, startTime, ERROR);
            error.errno = result;
            error.address = cpuDevice->PC;
            return(error);
        }
        
        /* Get the top 8 bits of the data. These contain the instruction */
        currentInstruction = (currentWord & 0xFFFFFFFF) >> 56;
        sprintf(debugString, "Instruction decoded: %x", currentInstruction);
        debug(debugString, startTime, INFO);
        
        
        
    }
    return(NULL);
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
