#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "./2204/2204.h"
#include "errors.h"
#include "assembler.h"

/* https://gist.github.com/panzi/6856583#gistcomment-1656524 */
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(__CYGWIN__)
    #include <windows.h>
    #define htobe64(x) (((uint64_t)htonl(((uint32_t)(((uint64_t)(x)) >> 32)))) | (((uint64_t)htonl(((uint32_t)(x)))) << 32))
#elif defined(__linux__)
    #include <endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__)
    #include <sys/endian.h>
#elif defined(__OpenBSD__)
    #include <sys/types.h>
#endif

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
    uint64_t lineNumber = 1;
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
        printf("%s", inputLine);
        result = assemble(inputLine, outputFile, lineNumber);
        printf("\n");
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
    char instruction[5] = "XXXX";
    
    memcpy(instruction, inputLine, 4);
    
    /* Determine instruction */
    if (!strcmp(instruction, "NOOP"))
    {
        word = NOOP;
        printf("%s -> %" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (SUCCESS);
    }
    
    else if (!strcmp(instruction, "STOP"))
    {
        word = STOP;
        printf("%s -> %" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (SUCCESS);
    }
    
    else if (!strcmp(instruction, "COPY"))
    {
        word = COPY;
        printf("%s -> %" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (twoArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "PRNT"))
    {
        word = PRNT;
        printf("%s -> %" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (oneArg(inputLine, outputFile));
    }
    
    else
    {
        return (ERR_UNKNOWN_INSTRUCTION);
    }
}

int oneArg(char *inputLine, FILE *outputFile)
{
    char arg[19];
    int lineLength;
    int col;
    int i;
    uint64_t word;
    
    lineLength = strlen(inputLine);
    
    /* Getting the length of the first address in the asm file */
    i = 0;
    for (col = 5; col < lineLength; col++)
    {
        if ((inputLine[col] != ',') || (inputLine[col] != ' ') || (inputLine[col] != ';') || (inputLine[col] != '\n') || (inputLine[col] != '\r'))
        {
            i++;
        }
        else
        {
            break;
        }
    }
    strncpy(arg, inputLine +  5, i - 1);
    word = strtoull(arg, NULL, 0);
    printf("%s -> %" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    return (SUCCESS);
}

int twoArgs(char *inputLine, FILE *outputFile)
{
    char arg[19];
    int lineLength;
    int startCol;
    int col;
    int i;
    uint64_t word;
    
    lineLength = strlen(inputLine);
    
    /* Getting the length of the first address in the asm file */
    i = 0;
    for (col = 5; col < lineLength; col++)
    {
        if (inputLine[col] != ',')
        {
            i++;
        }
        else
        {
            break;
        }
    }
    strncpy(arg, inputLine +  5, i);
    word = strtoull(arg, NULL, 0);
    printf("%s -> %" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    
    /* Getting the position of the second address in the asm file */
    for (col++; col < lineLength; col++)
    {
        if (inputLine[col] != ' ')
        {
            break;
        }
    }
    startCol = col;
    
    /* Getting the length of the second address in the asm file */
    i = 0;
    for (; col < lineLength; col++)
    {
        if ((inputLine[col] == ' ') || (inputLine[col] == ';') || (inputLine[col] == '\n') || (inputLine[col] == '\r'))
        {
            break;
        }
        i++;
    }
    strncpy(arg, inputLine + startCol, i);
    word = strtoull(arg, NULL, 0);
    printf("%s -> %" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    
    return (SUCCESS);
}