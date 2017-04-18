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

    uint8_t currentInstruction;
    uint64_t currentWord;
    uint64_t currentData;
    uint64_t sourceAddress;
} cpu_t;

void cpuInit(cpu_t *cpuDevice, uint64_t bootAddress, uint64_t registerCount);
err2204_t cpuRun(cpu_t *cpuDevice, ram_t *ramDevice);
int legalCopy(uint64_t source, uint64_t destination, cpu_t *cpuDevice, ram_t *ramDevice);
int memDirector(uint64_t address, cpu_t *cpuDevice, ram_t *ramDevice);
void debug(char *string, time_t startTime, int level);

int cpyf(cpu_t *cpuDevice, char *debugString);
int cpyt(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString);

#endif