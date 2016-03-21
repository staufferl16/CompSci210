// File: token.h

// Represents the set of all lexical items, such as opcodes, commas,
// labels, registers, and numbers.

#ifndef _TOKEN_H
#define _TOKEN_H

typedef enum { TC_ADD, TC_AND, TC_BLKW, TC_BR, TC_BRZ, TC_BRN, TC_BRP, 
               TC_BRNZ, TC_BRZP, TC_BRNZP, TC_BRNP, TC_COMMA, TC_END, TC_ERROR,
               TC_FILL, TC_GETC, TC_HALT, TC_IN, TC_INT, TC_JMP, TC_JSR, 
               TC_JSRR, TC_LABEL, TC_LD, TC_LDI, TC_LDR, TC_LEA, TC_NEWLINE, 
               TC_NOT, TC_ORIG, TC_OUT, TC_PUTS, TC_REG, TC_RET, TC_RTI, 
               TC_ST, TC_STI, TC_STR, TC_STRING_LIT, TC_STRINGZ, TC_TRAP
} tokenType;

// A token has a type, a source string (in uppercase), a binary string,
// and an int value.
typedef struct token{
    tokenType type;
    char* source;
    char* binary;
    int intValue;
} token;

void printToken(token t);

#endif