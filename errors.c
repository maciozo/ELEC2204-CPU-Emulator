#include <stdio.h>

#include "errors.h"

void printError(err2204_t *error)
{
    switch(error->errno)
    {
        case SUCCESS:
            fprintf(stderr, "Instruction at %x. The operation completed successfully.\n", error->address);
            break;

        case ERR_ADDRESS_OUT_OF_RANGE:
            fprintf(stderr, "Instruction at %x. The specified destination address is out of range.\n", error->address);
            break;
            
        case ERR_END_ADDRESS_OUT_OF_RANGE:
            fprintf(stderr, "Instruction at %x. The specified end address is out of range.\n", error->address);
            break;
            
        case ERR_RAM_ADDRESS_IN_USE:
            fprintf(stderr, "Instruction at %x. The specified RAM address is already in use.\n", error->address);
            break;
            
        default:
            fprintf(stderr, "Instruction at %x. Unknown error (%i%).\n", error->address, error->errno);
            break;
    }
}
