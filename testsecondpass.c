// File: testsecondpass.

#include <stdio.h>
#include "chario.h"
#include "symboltable.h"
#include "firstpass.h"
#include "secondpass.h"

FILE* openInputFile(int length, char* argVec[]){
    FILE* infile = fopen(argVec[1], "r");
    if (infile == NULL)
        printf("The input file does not exist in this directory\n");
    return infile;
}

FILE* openOutputFile(int length, char* argVec[], int pass){
    FILE* outfile = stdout;
    if (length == 3)
        outfile = fopen(argVec[2], "w");
    printf("\n%s %d\n", "Beginning pass", pass);
    return outfile;
}

FILE* openBinaryFile(char* argVec[]){
    char* sourceName = argVec[1];    
    int i = 0;
    while (sourceName[i] != '.')
        i++;
    sourceName[i + 1] = 'b';
    sourceName[i + 2] = 'i';
    sourceName[i + 3] = 'n';
    return fopen(sourceName, "w");
} 

void closeFiles(FILE* infile, FILE* outfile){
    fclose(infile);
    if (outfile != stdout) 
        fclose(outfile);
}
   
int main(int length, char *argVec[]){
    if (length == 1){
        printf("Usage:\n");
        printf("./testsecondpass <inputfile.asm> [<listingfile>]\n"); 
        return;
    }
    FILE* infile = openInputFile(length, argVec);
    FILE* outfile = openOutputFile(length, argVec, 1);
    if (infile == NULL)
        return;
    firstPass(infile, outfile);
    closeFiles(infile, outfile);
    if (getTotalErrors() == 0){
        infile = openInputFile(length, argVec);
        outfile = openOutputFile(length, argVec, 2);    
        FILE* binfile = openBinaryFile(argVec);
        secondPass(infile, outfile, binfile);
        closeFiles(infile, outfile);
        fclose(binfile);
    }
    reportErrors();
}