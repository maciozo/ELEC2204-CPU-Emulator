#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "./2204/2204.h"
#include "errors.h"
#include "assembler.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage assembler <input> <output>\n");
        return (1);
    }
    
    FILE *inputFile;
    FILE *outputFile;
    char inputLine[1024];
    uint64_t lineNumber = 0;
    int result;
    err2204_t error;
    
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        perror("Unable to open input file for reading");
        return (1);
    }
    
    outputFile = fopen(argv[2], "wb");
    if (inputFile == NULL)
    {
        perror("Unable to open output file for binary writing");
        return (1);
    }
    outputFile = fopen(argv[2], "ab");
    
    while (fgets(inputLine, 1024, inputFile))
    {
        lineNumber++;
        result = assemble(inputLine, outputFile, lineNumber);
        if (result != SUCCESS)
        {
            fprintf(stderr, "Line %" PRIu64 ": %i", lineNumber, result);
            error.errnum = result;
            error.address = lineNumber;
            printError(&error);
            return(result);
        }
    }
    
    return (0);
}

int assemble(char *inputLine, FILE *outputFile, uint64_t lineNumber)
{
    uint64_t word;
    char instruction[5] = "NOOP";
    char arg[19];
    int lineLength;
    int col;
    int i;
    
    memcpy(instruction, inputLine, 4);
    lineLength = strlen(inputLine);
    
    /* Determine instruction */
    if (!strcmp(instruction, "NOOP"))
    {
        word = NOOP;
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (SUCCESS);
    }
    
    else if (!strcmp(instruction, "COPY"))
    {
        word = COPY;
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        
        /* Getting the length of the first address in the asm file */
        i = 0;
        for (col = 5; col < lineLength; col++)
        {
            if (inputLine[col] != ',')
            {
                i++;
            }
        }
        strncpy(arg, inputLine + col, i);
        word = strtoull(arg, NULL, 16);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        
        /* Getting the position of the second address in the asm file */
        for (col = 5 + i; col < lineLength; col++)
        {
            if (inputLine[col] != ' ')
            {
                break;
            }
        }
        
        /* Getting the length of the second address in the asm file */
        i = 0;
        for (col; col < lineLength; col++)
        {
            if ((inputLine[col] == ' ') || (inputLine[col] == ';') || (inputLine[col] == '\n') || (inputLine[col] == '\r'))
            {
                break;
            }
            i++;
        }
        strncpy(arg, inputLine + col, i);
        word = strtoull(arg, NULL, 16);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        
        return (SUCCESS);
    }
    
    else
    {
        return (ERR_UNKNOWN_INSTRUCTION);
    }
}
