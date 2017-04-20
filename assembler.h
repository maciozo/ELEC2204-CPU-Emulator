#ifndef ASSEMBLER_2204_H
#define ASSEMBLER_2204_H

#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]);
int assemble(char *inputLine, FILE *outputFile, uint64_t lineNumber);

int oneArg(char *inputLine, FILE *outputFile);
int twoArgs(char *inputLine, FILE *outputFile);
int threeArgs(char *inputLine, FILE *outputFile);

#endif
