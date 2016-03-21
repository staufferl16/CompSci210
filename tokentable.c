// File: tokentable.c

#include <stdio.h>
#include <string.h>
#include "tokentable.h"

void initToken(tokenType t, char* src, char* bin, int intValue, int *index,
               token table[]){
    int i = (*index);
    table[i].type = t;
    table[i].source = src;
    table[i].binary = bin;
    table[i].intValue = intValue;
    (*index) = i + 1;
}

// Returns the index of the token associated with src or -1
// if it is not there.
int findToken(char* src, token table[], int length){
    int probe;
    for (probe = 0; probe < length; probe++)
        if (strcmp(src, table[probe].source) == 0)
            return probe;
    return -1;
}

void printTokenTable(token table[], int length){
    int i;
    for (i = 0; i < length; i++)
        printToken(table[i]);
}