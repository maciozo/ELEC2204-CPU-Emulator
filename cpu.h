#ifndef CPU_2204_H
#define CPU_2204_H

#include <stdint.h>
#include <stdio.h>

#include "ram.h"

#define ERROR 0
#define WARNING 1
#define INFO 2

#define CPU_DEBUG INFO

/* Memory destination devices */
#define DEV_INVALID -1
#define DEV_NULL 0
#define DEV_REG 1
#define DEV_RAM 2

typedef struct
{
    uint64_t PC;
    uint64_t *registers;
    uint64_t registerMax;

    uint8_t currentInstruction;
    uint64_t currentWord;
    uint64_t currentData;
    uint64_t sourceAddress;
} cpu_t;

void cpuInit(uint64_t ramAddress);
void cpuRun(cpu_t *cpuDevice, ram_t *ramDevice);
void debug(char *string)

#endif
