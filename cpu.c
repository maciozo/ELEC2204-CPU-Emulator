#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"
#include "errors.h"

#ifdef DEBUG
    #include <time.h>
#endif

void cpuInit(cpu_t *cpuDevice, uint64_t bootAddress, uint64_t registerCount)
{
    cpuDevice->PC = bootAddress;
    cpuDevice-registers = (uint64_t*) malloc(sizeof(uint64_t) * registerCount);
    cpuDevice->registerMax = registerCount;

    return(NULL);
}

err2204_t cpuRun(cpu_t *cpuDevice, ram_t *ramDevice)
{
    err2204_t error;
    char debugString[128];
    int result;

    #ifdef DEBUG
        time_t startTime = time(NULL);
        debugString = "CPU Started";
        debug(debugString, startTime, INFO);
    #endif


    while(1)
    {
        /* Reading instruction at the address specified by PC */
        sprintf(debugString, "Reading instruction at %x", cpuDevice->PC);
        debug(debugString, startTime, INFO);
        result = ramRead(ramDevice, cpuDevice->PC, &cpuDevice->currentWord);

        /* Did we fail to read the instruction? */
        if (result != SUCCESS)
        {
            sprintf(debugString, "Failed. Error %i", result);
            debug(debugString, startTime, ERROR);
            error.errno = result;
            error.address = cpuDevice->PC;
            return(error);
        }

        /* Get the top 8 bits of the data. These contain the instruction */
        cpuDevice->currentInstruction = (cpuDevice->currentWord >> 56) & 0xFF;
        sprintf(debugString, "Instruction: %x", cpuDevice->currentInstruction);
        debug(debugString, startTime, INFO);

        /* Get the bottom 56 bits. These contain the payload. */
        cpuDevice->currentData = cpuDevice->currentWord & 0x00FFFFFFFFFFFFFF;
        sprintf(debugString, "Payload: %x", cpuDevice->currentData);
        debug(debugString, startTime, INFO);

        /* Decode instruction */
        switch(cpuDevice->currentInstruction)
        {
            case NOOP:
                sprintf(debugString, "Instruction: NOOP");
                debug(debugString, startTime, INFO);
                result = SUCCESS;
                break;

            case CPYF:
                result = cpyf(cpuDevice, debugString);
                break;

            case CPYT:
                result = cpyt(cpuDevice, ramDevice, debugString);
                if (result != SUCCESS)
                {
                    error.errno = result;
                    error.address = cpuDevice->PC;
                    return(error);
                }
                break;

        }

    }
    return(NULL);
}

int cpyf(cpu_t *cpuDevice, char *debugString)
{
    sprintf(debugString, "Instruction: CPYF");
    debug(debugString, startTime, INFO);
    cpuDevice->sourceAddress = cpuDevice->currentData;
    return(SUCCESS);
}

int cpyt(cpu_t *cpuDevice, ram_t *ramDevice, char *debugString)
{
    sprintf(debugString, "Instruction: CPYF");
    debug(debugString, startTime, INFO);

    /* Determine destination device */
    switch (memDirector(cpuDevice->currentData, cpuDevice, ramDevice))
    {
        case DEV_INVALID:
            sprintf(debugString, "Invalid destination address: %x", cpuDevice->currentData);
            debug(debugString, startTime, ERROR);
            return (ERR_INVALID_ADDRESS);
            break;
            
        case DEV_NULL:
            sprintf(debugString, "Destination address is DEV_NULL");
            debug(debugString, startTime, WARNING);
            return (SUCCESS);
            break;
            
        case DEV_REG:
            sprintf(debugString, "Destination is register address: %x", cpuDevice->currentData);
            debug(debugString, startTime, INFO);
            result = legalCopy(cpuDevice->sourceAddress, cpuDevice->currentData, cpuDevice, ramDevice)
            if (result != SUCCESS)
            {
                sprintf(debugString, "Error copying data: %i", result);
                debug(debugString, startTime, ERROR);
                return (result);
            }

            /* Determine source device */
            switch (memDirector(cpuDevice->sourceAddress, cpuDevice, ramDevice))
            {
                case DEV_REG:
                    cpuDevice->registers[cpuDevice->currentData] = cpuDevice->registers[cpuDevice->sourceAddress];
                    break;
                case DEV_RAM:
                    result = ramRead(ramDevice, cpuDevice->sourceAddress, &(cpuDevice->registers[cpuDevice->currentData]));
                    if (result != SUCCESS)
                    {
                        sprintf(debugString, "Error reading from RAM: %i", result);
                        debug(debugString, startTime, ERROR);
                        return (result);
                    }
                    break;
            }
            return (SUCCESS);
            break;
        
        case DEV_RAM:
            sprintf(debugString, "Destination is RAM address: %x", cpuDevice->currentData);
            debug(debugString, startTime, INFO);
            result = legalCopy(cpuDevice->sourceAddress, cpuDevice->currentData, cpuDevice, ramDevice)
            if (result != SUCCESS)
            {
                sprintf(debugString, "Error copying data: %i", result);
                debug(debugString, startTime, ERROR);
                return (result);
            }
            
            result = ramWrite(ramDevice, cpuDevice->currentData, cpuDevice->registers[cpuDevice->sourceAddress]);
            if (result != SUCCESS)
            {
                sprintf(debugString, "Error writing to RAM: %i", result);
                debug(debugString, startTime, ERROR);
                return (result);
            }
            return (SUCCESS);
            break;
    }

    return();
}

int legalCopy(uint64_t source, uint64_t destination, cpu_t *cpuDevice, ram_t *ramDevice)
{
    int sourceDev = memDirector(source, cpuDevice, ramDevice);
    int destinationDev = memDirector(destination, cpuDevice, ramDevice);
    
    switch (sourceDev)
    {
        case DEV_INVALID:
            return(ERR_READ_FROM_INVALID);
            break;
        case DEV_NULL:
            return(SUCCESS);
            break;
        case DEV_REG:
            return(SUCCESS);
            break;
        case DEV_RAM:
            switch (destinationDev)
            {
                case DEV_INVALID:
                    return(ERR_COPY_TO_INVALID);
                    break;
                case DEV_NULL:
                    return(SUCCESS);
                    break;
                case DEV_REG:
                    return(SUCCESS);
                    break;
                case DEV_RAM:
                    return(ERR_ILLEGAL_MEMORY_COPY);
                    break;
                default:
                    return(ERR_UNEXPECTED_RESULT);
                    break;
            }
            break;
        default:
            return(ERR_UNEXPECTED_RESULT);
            break;
    }
}

int memDirector(uint64_t address, cpu_t *cpuDevice, ram_t *ramDevice)
{
    if (address > 0x00FFFFFFFFFFFFFF)
    {
        return(DEV_INVALID);
    }

    if (address == 0)
    {
        return(DEV_NULL);
    }

    if (address <= cpuDevice->registerMax)
    {
        return(DEV_REG);
    }

    if ((address >= ramDevice->address) & (address <= ramDevice->addressMax))
    {
        return(DEV_RAM);
    }

    return(DEV_INVALID);
}

void debug(char *string, time_t startTime, int level)
{
    #ifdef DEBUG
        if (level <= CPU_DEBUG)
        {
            double seconds;

            time_t currentTime = time(NULL);
            seconds = difftime(currentTime, startTime);
            printf("[%f] %s\n", seconds, string);
        }
    #endif
    return(NULL);
}
