#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

#include "cpu.h"
#include "bus.h"

void cpuInit(bus_t* systemBus, FILE* bootloader, uint8_t ramAddress)
{
    cpu_t cpuInfo;
    pthread_t cpuThread;
    
    cpuInfo.systemBus = &systemBus;
    cpuInfo.ramAddress = *ramAddress;
    cpuInfo.PC = 0;
    
    if (pthread_create(&cpuThread, NULL, &cpuRun, (void*)&cpuInfo)
    {
        fprintf(stderr, "Failed to start CPU thread.\n");
        return(1);
    }
}

void *cpuRun(void *cpuInfo)
{
    return(NULL);
}