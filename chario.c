// File: chario.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tools.h"
#include "chario.h"

#define FIELD_WIDTH 4
#define TRUE 1

static char inputLine[MAX_COLUMNS];
static int inputLineNumber;
static int totalErrors;
static FILE* infile;
static FILE* outfile;

void initChario(FILE* inf, FILE* outf){
    inputLineNumber = 0;
    totalErrors = 0;
    infile = inf;
    outfile = outf;
}

int getTotalErrors(){
    return totalErrors;
}

void putError(char* errorMessage){
      totalErrors++;
      printf("Error on line %d: %s\n", inputLineNumber, errorMessage);
}

void reportErrors(){
     printf("\nFinished.  ");
     if (totalErrors == 0)
         printf("No errors reported.\n");
     else if (totalErrors == 1) 
         printf("1 error reported.\n");
     else
         printf("%d errors reported.\n", totalErrors);
}

// Returns NULL if the end of file has been reached
// Otherwise, returns the next line of code, after skipping any
// leading blank lines or comments.
char* nextCodeLine(){
    while (TRUE){
        char* result = fgets(inputLine, MAX_COLUMNS, infile);
        if (result == NULL)
            return NULL;
        inputLineNumber++;
        fprintf(outfile, "%*d> ", FIELD_WIDTH, inputLineNumber);
        fputs(inputLine, outfile);
        int index = skipBlanks(inputLine, 0);
        if (inputLine[index] != ';' && inputLine[index] != '\n' &&
            inputLine[index] != 0)
            return inputLine;
    }
    return NULL;
}        