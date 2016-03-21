#include <stdio.h>
#include "token.h"
#include "scanner.h"

void processFile(FILE *infile, FILE *outfile);

int main(int length, char *argVec[]){
    if (length == 1) 
		return;
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
	processFile(infile, outfile);
	fclose(infile);
	if (outfile != stdout) 
		fclose(outfile);
}

void processFile(FILE *infile, FILE *outfile){
    initScanner(infile, outfile);
    int count = 0;
    while (nextInstruction()){
        printToken(nextToken());
        count++;
    }
    printf("\n%d total tokens.\n", count);   
} 
