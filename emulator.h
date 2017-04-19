#include <stdint.h>
#include "./libconfig/lib/libconfig.h"

#include "cpu.h"
#include "ram.h"
#include "errors.h"

int main(int argc, char* argv[]);
int getRamInfo(config_t *config, uint64_t *ramAddress, uint64_t *ramSize);
err2204_t boot(const char *bootloaderFilename, ram_t *ramDevice, cpu_t *cpuDevice);
uint64_t getRegisterCount(config_t *config);
