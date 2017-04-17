#include <stdio.h>
#include <stdint.h>

#include "cpu.h"

void cpuInit(uint8_t ramAddress)
{
    cpu_t cpuInfo;
    
    cpuInfo.ramAddress = *ramAddress;
    cpuInfo.PC = 0;
    
    return(NULL);
}

void cpuRun(cpu_t *cpuInfo)
{
    return(NULL);
}