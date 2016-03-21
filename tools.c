// File: tools.c

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "tools.h"

// Converts buffer to uppercase
void makeUppercase(char buffer[]){
    int index;
    for (index = 0; buffer[index] != 0; index++)
            buffer[index] = toupper(buffer[index]);
}

// Like strcpy, but creates storage for and returns the new string.
char* copyString(char originalString[]){
    char* newString = malloc(sizeof(char) * strlen(originalString) + 1);
    strcpy(newString, originalString);
    return newString;
}

// Returns the position of the first non-blank character in line,
// starting from position startPos.
int skipBlanks(char* line, int startPos){
    while (line[startPos] == ' ' || line[startPos] == '\t')
        startPos++;
    return startPos;
}

void invertBits(char* bitString){
    int i;
    for (i = 0; bitString[i] != 0; i++)
        if (bitString[i] == '1')
            bitString[i] = '0';
        else
            bitString[i] = '1';
}

void addOne(char* bitString){
    char carry = '1';
    int i = strlen(bitString) - 1;
    while (i > 0){
        if (carry == '1' && bitString[i] == '1'){
            bitString[i] = '0';
            i--;
        }
        else{
            bitString[i] = '1';
            break;
        }
    }
}

char* unsignedBinary(int number, int numBits){
    char* newString = malloc(sizeof(char) * numBits + 1);
    newString[numBits] = 0;
    numBits--;
    while (number > 0){
        newString[numBits] = (number % 2) + '0';
        number /= 2;
        numBits--;
    }
    while (numBits >= 0){
        newString[numBits] = '0';
        numBits--;
    }
    return newString;
}

char* signedBinary(int number, int numBits){
    char* newString = unsignedBinary(abs(number), numBits);
    if (number < 0){
        invertBits(newString);
        addOne(newString);
    }
    return newString;
}