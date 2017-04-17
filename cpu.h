#ifndef CPU_2204_H
#define CPU_2204_H

#include <stdint.h>
#include <stdio.h>

typedef struct
{
    uint8_t ramAddress;
    uint64_t PC;
    uint64_t registers[64];
} cpu_t;

void cpuInit(uint8_t ramAddress);
void cpuRun(cpu_t *cpuInfo);

#endif
