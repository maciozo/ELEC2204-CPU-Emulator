#include <stdio.h>
#include <inttypes.h>

#include "errors.h"

void printError(err2204_t *error)
{
    switch(error->errnum)
    {
        case SUCCESS:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " SUCCESS_STR "\n", error->address);
            break;

        case ERR_ADDRESS_OUT_OF_RANGE:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_ADDRESS_OUT_OF_RANGE_STR "\n", error->address);
            break;

        case ERR_END_ADDRESS_OUT_OF_RANGE:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_END_ADDRESS_OUT_OF_RANGE_STR "\n", error->address);
            break;

        case ERR_RAM_ADDRESS_IN_USE:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_RAM_ADDRESS_IN_USE_STR "\n", error->address);
            break;

        case ERR_INVALID_ADDRESS:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_INVALID_ADDRESS_STR "\n", error->address);
            break;

        case ERR_ILLEGAL_MEMORY_COPY:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_ILLEGAL_MEMORY_COPY_STR "\n", error->address);
            break;

        case ERR_COPY_TO_INVALID:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_COPY_TO_INVALID_STR "\n", error->address);
            break;

        case ERR_READ_FROM_INVALID:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_READ_FROM_INVALID_STR "\n", error->address);
            break;

        case ERR_UNEXPECTED_RESULT:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_UNEXPECTED_RESULT_STR "\n", error->address);
            break;
            
        case ERR_UNKNOWN_INSTRUCTION:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_UNKNOWN_INSTRUCTION_STR "\n", error->address);
            break;
            
        case ERR_CPU_BREAK:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_CPU_BREAK_STR "\n", error->address);
            break;
            
        case ERR_ADDRESS_TOO_HIGH:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_ADDRESS_TOO_HIGH_STR "\n", error->address);
            break;
            
        case ERR_ADDRESS_TOO_LOW:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". " ERR_ADDRESS_TOO_LOW_STR "\n", error->address);
            break;

        default:
            fprintf(stderr, "Instruction at 0x%" PRIx64 ". Unknown error (%i).\n", error->address, error->errnum);
            break;
    }
    return;
}
