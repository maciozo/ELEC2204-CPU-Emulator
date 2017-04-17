#include <stdint.h>

/* State that says an address is free */
#define RAM_FREE 0

/* State that says an address is in use */
#define RAM_USED 1

#define ERR_ADDRESS_OUT_OF_RANGE 255

typedef struct
{
    /* First memory address */
    uint8_t address;
    
    /* Size of the RAM. ramSize*64 bits */
    uint64_t size;
    
    /* The RAM array itself */
    uint64_t *ram;
    
    /* Stores the state of each memory address */
    uint8_t *states;
} ram_t;

void ramInit(uint8_t *ramAddress, uint64_t *ramSize, FILE *bootloader,
            ram_t *ramDevice);
void *ramRun(void *ramInfo);
int ramRead(ram_t *ramDevice, uint64_t address, uint64_t *readTo);
int ramWrite(ram_t *ramDevice, uint64_t address, uint64_t data);
int ramFree(ram_t *ramDevice, uint64_t address);
uint8_t ramState(ram_t *ramDevice, uint64_t address);
