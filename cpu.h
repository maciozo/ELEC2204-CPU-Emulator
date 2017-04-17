#ifndef CPU_2204_H
#define CPU_2204_H

#include <stdint.h>
#include <stdio.h>

#include "ram.h"

#define ERROR 0
#define WARNING 1
#define INFO 2

#define CPU_DEBUG INFO

typedef struct
{
    uint64_t ramAddress;
    uint64_t PC;
    uint64_t registers[64];
} cpu_t;

void cpuInit(uint64_t ramAddress);
void cpuRun(cpu_t *cpuDevice, ram_t *ramDevice);
void debug(char *string)

#endif
