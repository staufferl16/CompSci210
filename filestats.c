/*
Author: YOUR NAME GOES HERE

This program prints statistics on a text file and prints a numbered
listing to an output file or to the display.
*/

#include <stdio.h>

void processFile(FILE *infile, FILE *outfile);

int main(int length, char *argVec[]){
    if (length == 1){ 
        printf("Usage: ./filestats <input file> [<output file>]\n");
	return; 
    }   
    FILE *infile = fopen(argVec[1], "r");
    if (infile == NULL){
	printf("The input file does not exist in this directory\n");
	return;
    }
    FILE *outfile;
    if (length == 3)
	outfile = fopen(argVec[2], "w");    // Using an output file
    else
	outfile = stdout;                   // Using the terminal
    processFile(infile, outfile);
    fclose(infile);
    if (outfile != stdout) 
	fclose(outfile);
}

/*
 * Prints a numbered listing of the input file to
 * the output file
 */
void processFile(FILE *infile, FILE *outfile){
    int max = 80;
    int fieldWidth = 4;
    char line[max];
    int lineNumber = 1;
    while (fgets(line, max, infile)){
        fprintf(outfile, "%*d%s", fieldWidth, lineNumber, "> ");  
        fputs(line, outfile);
        lineNumber++;
    }
}

