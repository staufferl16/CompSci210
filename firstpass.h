// File: firstpass.h

#include <stdio.h>

#define DEFAULT_START_ADDRESS 12288   // x3000
#define MAX_ADDRESS 65535             // 16-bit address

void firstPass(FILE *infile, FILE *outfile);
