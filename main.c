#include <stdio.h>
#include <stdint.h>
#include "./libconfig-1.5/lib/libconfig.h"
#include <sys/stat.h>
#include <stdlib.h>

#include "main.h"
#include "cpu.h"
#include "ram.h"
#include "errors.h"

int main(int argc, char* argv[])
{
    cpu_t cpuDevice;
    ram_t ramDevice;

    const char *bootloaderFilename;
    FILE *bootloader;

    uint64_t ramAddress;
    uint64_t ramSize;
    
    uint64_t registerCount;

    config_t config;
    config_init(&config);
    
    err2204_t result;

    /* Read the file. If there is an error, report it and exit. */
    if(! config_read_file(&config, "example.cfg"))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&config),
            config_error_line(&config), config_error_text(&config));
        config_destroy(&config);
        return(1);
    }

    /* Get the bootloader filename. */
    if(config_lookup_string(&config, "bootloader", &bootloaderFilename))
    {
        printf("Loading: %s\n", bootloaderFilename);
        bootloader = fopen(bootloaderFilename, "rb");
    }
    else
    {
        fprintf(stderr, "No bootloader specified\n");
        return(1);
    }

    if (bootloader == NULL)
    {
        perror("Unable to open bootloader file for reading\n");
        return(1);
    }
    fclose(bootloader);

    getRamInfo(&config, &ramAddress, &ramSize);
    
    registerCount = getRegisterCount(&config);
    if (registerCount)
    {
        return(1);
    }

    ramInit(&ramDevice, ramAddress, ramSize);
    cpuInit(&cpuDevice, ramAddress, registerCount);
    result = boot(bootloaderFilename, &ramDevice, &cpuDevice);
    if (result.errnum != SUCCESS)
    {
        printError(&result);
        return(result.errnum);
    }
    return(0);
}

uint64_t getRegisterCount(config_t *config)
{
    int64_t registerCount;
    
    /* Making sure that the registerCount has been defined in the config */
    if(!config_lookup_int64(config, "registerCount", &registerCount))
    {
        fprintf(stderr, "No registerCount defined.\n");
        return(0);
    }
    
    if (registerCount < 1)
    {
        fprintf(stderr, "At least one CPU register is required.\n");
        return(0);
    }

    return((uint64_t)registerCount);
}

int getRamInfo(config_t *config, uint64_t *ramAddress, uint64_t *ramSize)
{
    int64_t addr;
    int64_t size;

    /* Making sure that the RAM has been defined in the config */
    if(!config_lookup_int64(config, "ram", &addr))
    {
        fprintf(stderr, "No RAM device defined.\n");
        return(1);
    }

    /* Getting the device address of the RAM */
    if(config_lookup_int64(config, "ram.address", &addr))
    {
        if ((addr == 0) | (addr > 0x00FFFFFF))
        {
            fprintf(stderr, "Invalid RAM device address.\n");
            return(1);
        }
        *ramAddress = (uint64_t) addr;
    }
    else
    {
        fprintf(stderr, "No RAM address defined.\n");
        return(1);
    }

    if(config_lookup_int64(config, "ram.size", &size))
    {
        if (size == 0)
        {
            fprintf(stderr, "Invalid RAM size: 0\n");
            return(1);
        }
        *ramSize = (uint64_t) size;
    }
    else
    {
        fprintf(stderr, "No RAM size defined.\n");
        return(1);
    }

    return(0);
}

err2204_t boot(const char *bootloaderFilename, ram_t *ramDevice, cpu_t *cpuDevice)
{
    struct stat stbuf;
    int bootloaderLength;
    FILE *bootloaderFd;

    /* Getting the length of the bootloader in bytes */
    stat(bootloaderFilename, &stbuf);
    bootloaderLength = stbuf.st_size;
    realloc(&stbuf, 0); /* Deallocate stat buffer - no longer needed. */

    /* Writing data from bootloader to the front of the RAM */
    bootloaderFd = fopen(bootloaderFilename, "rb");
    fread(ramDevice->ram, sizeof(uint64_t), bootloaderLength / 8, bootloaderFd);
    fclose(bootloaderFd);

    return(cpuRun(cpuDevice, ramDevice));
}
