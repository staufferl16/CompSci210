// File: tokentable.h

#include "token.h"

// Initializes token, inserts it at index, and increments index.
// Assumes that index < size of table array.
void initToken(tokenType t, char* src, char* bin, int intValue, int *index,
               token table[]);

// Returns the index of the token associated with src or -1
// if it is not there.
int findToken(char* src, token table[], int length);

// Prints the table in three columns
void printTokenTable(token table[], int length);   