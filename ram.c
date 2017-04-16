#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>

#include "bus.h"

void ramInit(bus_t *systemBus, uint8_t *ramAddress, uint64_t *ramSize,
                FILE *bootloader)
{
    pthread_t ramThread;
    ram_t ramInfo;
    
    ramInfo.systemBus = &systemBus;
    ramInfo.ramAddress = *ramAddress;
    ramInfo.ramSize = *ramSize;
    
    if (pthread_create(&ramThread, NULL, &ramRun, (void*)&ramInfo)
    {
        fprintf(stderr, "Failed to start RAM thread.\n");
        return(1);
    }
}

void *ramRun(void *ramInfo)
{
    uint64_t *ram;
    ram = (uint64_t*) malloc(sizeof(uint64_t) * ramInfo->ramSize);
    
}