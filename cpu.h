#ifndef CPU_2204_H
#define CPU_2204_H

#include <stdint.h>
#include <stdio.h>

#include "ram.h"
#include "errors.h"

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
    uint64_t currentInstruction;
    uint64_t arguments[4];
} cpu_t;

void cpuInit(cpu_t *cpuDevice, uint64_t bootAddress, uint64_t registerCount);
err2204_t cpuRun(cpu_t *cpuDevice, ram_t *ramDevice);
int memDirector(uint64_t address, cpu_t *cpuDevice, ram_t *ramDevice);
void debug(char *string, time_t startTime, int level);
err2204_t checkResult(int result, uint64_t address, char *debugString, const char *errorText, time_t startTime);

#endif
