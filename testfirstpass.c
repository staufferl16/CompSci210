// File: testfirstpass.

#include <stdio.h>
#include "chario.h"
#include "symboltable.h"
#include "firstpass.h"

int main(int length, char *argVec[]){
    if (length == 1){
        printf("Usage:\n");
        printf("./testfirstpass <inputfile.asm> [<listingfile>]\n"); 
        return;
    }
    FILE *infile = fopen(argVec[1], "r");
    if (infile == NULL){
        printf("The input file does not exist in this directory\n");
        return;
    }
    FILE *outfile;
    if (length == 3)
        outfile = fopen(argVec[2], "w");
    else
        outfile = stdout;
    firstPass(infile, outfile);
    fclose(infile);
    if (outfile != stdout) 
        fclose(outfile);
    reportErrors();
    printSymbolTable();
}