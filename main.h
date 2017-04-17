#include <stdint.h>
#include <libconfig.h>

#include "cpu.h"
#include "ram.h"

int main(int argc, char* argv[]);
int getRamInfo(config_t *config, uint64_t *ramAddress, uint64_t *ramSize);
int boot(char *bootloader, ram_t *ramDevice, cpu_t *cpuDevice);
