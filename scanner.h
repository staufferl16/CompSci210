// File: scanner.h

#ifndef _SCANNER_H
#define _SCANNER_H

#include "token.h"

void initScanner(FILE* infile, FILE* outfile);

// Must be run to get the first instruction, and after a token
// is a newline.
// Can be run after the first token is scanned to advance to
// the next instruction on the assembler's first pass.
// Returns 0 if the end of file has been reached. 
int nextInstruction();

// Advances to the next token, if there is one, in the
// instruction, and returns the token just scanned.
// Returns the end of line token when the instruction has 
// been completely scanned.
// Ignores program comments.
token nextToken();

#endif