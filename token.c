// File: token.c

#include <stdio.h>
#include "token.h"

void printToken(token t){
    printf("Type: %d\nSource: %s\nBinary: %s\nInt value: %d\n\n", 
           t.type, t.source, t.binary, t.intValue); 
}