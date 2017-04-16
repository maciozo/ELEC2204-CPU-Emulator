#include <stdint.h>
#include "bus.h"

typedef struct
{
    uint8_t ramAddress;
    uint64_t ramSize;
    bus_t *systemBus;
} ram_t;

void ramInit(bus_t *systemBus, uint8_t *ramAddress, uint64_t *ramSize,
                FILE *bootloader);
void *ramRun(void *ramInfo);
