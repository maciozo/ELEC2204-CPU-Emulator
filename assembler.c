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
        printf("Usage: assembler <input> <output>\n");
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
        printf("%s", inputLine);
        result = assemble(inputLine, outputFile, lineNumber);
        printf("\n");
        if (result != SUCCESS)
        {
            fprintf(stderr, "Line %" PRIu64 ": (error %i) ", lineNumber, result);
            error.errnum = result;
            error.address = lineNumber;
            printError(&error);
            return(result);
        }
        printf("================================================================================\n");
    }
    
    return (0);
}

int assemble(char *inputLine, FILE *outputFile, uint64_t lineNumber)
{
    uint64_t word;
    char instruction[5] = "XXXX";
    int col;
    int lineLength;
    
    lineLength = strlen(inputLine);
    for (col = 0; col < lineLength; col++)
    {
        if (!((inputLine[col] == '\n') || (inputLine[col] == '\r') || (inputLine[col] == ' ') || (inputLine[col] == '\0') || (inputLine[col] == ';')))
        {
            break;
        }
        if (inputLine[col] == ';')
        {
            printf("Comment\n");
            return(SUCCESS);
        }
    }
    if (col == lineLength)
    {
        printf("Blank line\n");
        return (SUCCESS);
    }
    
    memcpy(instruction, inputLine + col, 4);
    
    /* Determine instruction */
    if (!strcmp(instruction, "NOOP"))
    {
        word = NOOP;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (SUCCESS);
    }
    
    else if (!strcmp(instruction, "STOP"))
    {
        word = STOP;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (SUCCESS);
    }
    
    else if (!strcmp(instruction, "COPY"))
    {
        word = COPY;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (twoArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "PRNT"))
    {
        word = PRNT;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (oneArg(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JUML"))
    {
        word = JUML;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (oneArg(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "STOR"))
    {
        word = STOR;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (twoArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "FREE"))
    {
        word = FREE;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (twoArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "ADDA"))
    {
        word = ADDA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "SUBA"))
    {
        word = SUBA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "PRND"))
    {
        word = PRND;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (oneArg(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "ORAD"))
    {
        word = ORAD;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "ANDA"))
    {
        word = ANDA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "NOTA"))
    {
        word = NOTA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (twoArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "NNDA"))
    {
        word = NNDA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "NORA"))
    {
        word = NORA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "XORA"))
    {
        word = XORA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JEQA"))
    {
        word = JEQA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JEQP"))
    {
        word = JEQP;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JGTP"))
    {
        word = JGTP;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JLTP"))
    {
        word = JLTP;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JEQN"))
    {
        word = JEQN;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JGTN"))
    {
        word = JGTN;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "JLTN"))
    {
        word = JLTN;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "MULA"))
    {
        word = MULA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "DIVA"))
    {
        word = DIVA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
    }
    
    else if (!strcmp(instruction, "MODA"))
    {
        word = MODA;
        printf("%s -> 0x%" PRIx64 "\n", instruction, word);
        fwrite(&word, sizeof(uint64_t), 1, outputFile);
        return (threeArgs(inputLine, outputFile));
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
    printf("%s -> 0x%" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    return (SUCCESS);
}

int twoArgs(char *inputLine, FILE *outputFile)
{
    char arg[19] = "                  ";
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
    printf("%s -> 0x%" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    strcpy(arg, "                  ");
    
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
    printf("%s -> 0x%" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    
    return (SUCCESS);
}

int threeArgs(char *inputLine, FILE *outputFile)
{
    char arg[19] = "                  ";
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
    printf("%s -> 0x%" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    strcpy(arg, "                  ");
    
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
        if (inputLine[col] != ',')
        {
            i++;
        }
        else
        {
            break;
        }
    }
    strncpy(arg, inputLine + startCol, i);
    word = strtoull(arg, NULL, 0);
    printf("%s -> 0x%" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    strcpy(arg, "                  ");
    
    /* Getting the position of the third address in the asm file */
    for (col++; col < lineLength; col++)
    {
        if (inputLine[col] != ' ')
        {
            break;
        }
    }
    startCol = col;
    
    /* Getting the length of the third address in the asm file */
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
    printf("%s -> 0x%" PRIx64 "\n", arg, word);
    fwrite(&word, sizeof(uint64_t), 1, outputFile);
    
    return (SUCCESS);
}
