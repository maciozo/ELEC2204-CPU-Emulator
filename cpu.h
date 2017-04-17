#ifndef CPU_2204_H
#define CPU_2204_H

#include <stdint.h>
#include <stdio.h>

#include "ram.h"

typedef struct
{
    uint64_t ramAddress;
    uint64_t PC;
    uint64_t registers[64];
} cpu_t;

void cpuInit(uint64_t ramAddress);
void cpuRun(cpu_t *cpuDevice, ram_t *ramDevice);

#endif
