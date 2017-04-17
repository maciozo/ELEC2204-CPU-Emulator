#include <stdint.h>
#include <stdio.h>

#include "bus.h"

typedef struct
{
    bus_t *systemBus;
    uint8_t ramAddress;
    uint64_t PC;
    uint64_t registers[64];
} cpu_t;

void cpuInit(bus_t* systemBus, FILE* bootloader, uint8_t ramAddress);
void cpuRun(cpu_t *cpuInfo);
