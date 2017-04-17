#include <stdio.h>
#include <stdint.h>
#include <libconfig.h>
#include <sys/stat.h>

#include "main.h"
#include "cpu.h"
#include "ram.h"

int main(int argc, char* argv[])
{
    bus_t systemBus;

    const char *bootloaderFilename;
    FILE *bootloader;

    const uint8_t ramAddress;
    const uint64_t ramSize;

    config_t config;
    config_init(&config);

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
        fclose(bootloader);
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

    getRamInfo(&config, &ramAddress, &ramSize);

    ramInit(&systemBus, &ramAddress, &ramSize);
    cpuInit(&systemBus);
    return(0);
}

int getRamInfo(config_t *config, uint64_t *ramAddress, uint64_t *ramSize)
{
    int8_t addr;
    int64_t size;

    /* Making sure that the RAM has been defined in the config */
    if(!config_lookup_int64(&config, "ram", &addr))
    {
        fprintf(stderr, "No RAM device defined.\n");
        return(1);
    }

    /* Getting the device address of the RAM */
    if(config_lookup_int64(&config, "ram.address", &addr))
    {
        if ((addr == 0) | (addr > 0xFF))
        {
            fprintf(stderr, "Invalid RAM device address.\n");
            return(1);
        }
        ramAddress = (uint64_t) addr;
    }
    else
    {
        fprintf(stderr, "No RAM address defined.\n");
        return(1);
    }

    if(config_lookup_int64(&config, "ram.size", &size))
    {
        if (size == 0)
        {
            fprintf(stderr, "Invalid RAM size: 0\n");
            return(1);
        }
        ramSize = (uint64_t) size;
    }
    else
    {
        fprintf(stderr, "No RAM size defined.\n");
        return(1);
    }

    return(0);
}

int boot(char *bootloader, ram_t *ramDevice, cpu_t *cpuDevice)
{
    struct stat stbuf;
    int bootloaderLength;
    FILE *bootloaderFd;

    /* Getting the length of the bootloader in bytes */
    stat(bootloader, stbuf);
    bootloaderLength = stbuf->st_size;
    realloc(&stbuf, 0); /* Deallocate stat buffer - no longer needed. */

    /* Writing data from bootloader to the front of the RAM */
    bootloaderFd = fopen(bootloaderFilename, "rb");
    fread(ramDevice->ram, sizeof(uint64_t), bootloaderLength / 8, bootloaderFd);
    fclose(bootloaderFd);

    
}
