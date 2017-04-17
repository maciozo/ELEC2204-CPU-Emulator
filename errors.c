#include <stdio.h>

#include "errors.h"

void printError(err2204_t *error)
{
    switch(error->errno)
    {
        case SUCCESS:
            fprintf(stderr, "Instruction at %x. The operation completed successfully. (SUCCESS)\n", error->address);
            break;

        case ERR_ADDRESS_OUT_OF_RANGE:
            fprintf(stderr, "Instruction at %x. The specified destination address is out of range. (ERR_ADDRESS_OUT_OF_RANGE)\n", error->address);
            break;
            
        case ERR_END_ADDRESS_OUT_OF_RANGE:
            fprintf(stderr, "Instruction at %x. The specified end address is out of range. (ERR_END_ADDRESS_OUT_OF_RANGE)\n", error->address);
            break;
            
        case ERR_RAM_ADDRESS_IN_USE:
            fprintf(stderr, "Instruction at %x. The specified RAM address is already in use. (ERR_RAM_ADDRESS_IN_USE)\n", error->address);
            break;
            
        case ERR_INVALID_ADDRESS:
            fprintf(stderr, "Instruction at %x. The specified address is invalid. (ERR_INVALID_ADDRESS)\n", error->address);
            break;
            
        case ERR_ILLEGAL_MEMORY_COPY:
            fprintf(stderr, "Instruction at %x. Cannot copy from the specified source address to the specified destination address. Most likely because the program attempted to copy data without going through the CPU registers. (ERR_ILLEGAL_MEMORY_COPY)\n", error->address);
            break;
            
        case ERR_COPY_TO_INVALID:
            fprintf(stderr, "Instruction at %x. The program tried to copy data to an invalid address. (ERR_COPY_TO_INVALID)\n", error->address);
            break;
            
        case ERR_READ_FROM_INVALID:
            fprintf(stderr, "Instruction at %x. The program tried to read data from an invalid address. (ERR_READ_FROM_INVALID)\n", error->address);
            break;
            
        default:
            fprintf(stderr, "Instruction at %x. Unknown error (%i%).\n", error->address, error->errno);
            break;
    }
}
