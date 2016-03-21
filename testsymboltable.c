/*
Author: Ken Lambert
File: testsymbolable.c
Test driver for the symbol table.
*/

#include <stdio.h>
#include "symboltable.h"

int main(){
    initSymbolTable();
    printf("Printing empty table:\n");
    printSymbolTable();
    char* enterResult = enterSymbol("SECOND", 45);
    printf("Expect SECOND: %s\n", enterResult);
    printf("Printing table with one entry:\n");
    printSymbolTable();
    enterResult = enterSymbol("FIRST", 30);
    printf("Expect FIRST: %s\n", enterResult);
    printf("Printing table with two entries:\n");
    printSymbolTable();
    int findResult = findSymbol("SECOND");
    printf("Expect 45: %d\n", findResult);
    findResult = findSymbol("THIRD");
    printf("Expect -1: %d\n", findResult);
    enterResult = enterSymbol("SECOND", 56);
    printf("Expect 0: %p\n", enterResult);
}

