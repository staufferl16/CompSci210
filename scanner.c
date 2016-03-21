// File: scanner.c

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tools.h"
#include "chario.h"
#include "token.h"
#include "scanner.h"
#include "tokentable.h"

#define MAX_OPCODES 29
#define MAX_REGISTERS 8
#define MAX_DIRECTIVES 5

static token opcodeTable[MAX_OPCODES];
static token registerTable[MAX_REGISTERS];
static token directiveTable[MAX_DIRECTIVES];
static char* codeLine;
static int codeLineNumber;
static int codeLineColumn;
static char tokenBuffer[MAX_COLUMNS];
static int tokenLength;
static token globalToken;

void initOpcodeTable(){
    int index = 0;
    initToken(TC_ADD,   "ADD",   "0001",             0, &index, opcodeTable);
    initToken(TC_AND,   "AND",   "0101",             0, &index, opcodeTable);
    initToken(TC_BR,    "BR",    "0000111",          0, &index, opcodeTable);
    initToken(TC_BRZ,   "BRZ",   "0000010",          0, &index, opcodeTable);
    initToken(TC_BRN,   "BRN",   "0000100",          0, &index, opcodeTable);
    initToken(TC_BRP,   "BRP",   "0000001",          0, &index, opcodeTable);
    initToken(TC_BRNZ,  "BRNZ",  "0000110",          0, &index, opcodeTable);
    initToken(TC_BRZP,  "BRZP",  "0000011",          0, &index, opcodeTable);
    initToken(TC_BRNZP, "BRNZP", "0000111",          0, &index, opcodeTable);
    initToken(TC_BRNP,  "BRNP",  "0000101",          0, &index, opcodeTable);
    initToken(TC_GETC,  "GETC",  "1111000000100000", 0, &index, opcodeTable);
    initToken(TC_HALT,  "HALT",  "1111000000100101", 0, &index, opcodeTable);
    initToken(TC_IN,    "IN",    "1111000000010011", 0, &index, opcodeTable);
    initToken(TC_JMP,   "JMP",   "1100000",          0, &index, opcodeTable);
    initToken(TC_JSR,   "JSR",   "01001",            0, &index, opcodeTable);
    initToken(TC_JSRR,  "JSRR",  "01000",            0, &index, opcodeTable);
    initToken(TC_LD,    "LD",    "0010",             0, &index, opcodeTable);
    initToken(TC_LDI,   "LDI",   "1010",             0, &index, opcodeTable);
    initToken(TC_LDR,   "LDR",   "0110",             0, &index, opcodeTable);
    initToken(TC_LEA,   "LEA",   "1110",             0, &index, opcodeTable);
    initToken(TC_NOT,   "NOT",   "1001",             0, &index, opcodeTable);
    initToken(TC_OUT,   "OUT",   "1111000000100001", 0, &index, opcodeTable);
    initToken(TC_PUTS,  "PUTS",  "1111000000100010", 0, &index, opcodeTable);
    initToken(TC_RET,   "RET",   "1100000111000000", 0, &index, opcodeTable);
    initToken(TC_RTI,   "RTI",   "1000000000000000", 0, &index, opcodeTable);
    initToken(TC_ST,    "ST",    "0011",             0, &index, opcodeTable);
    initToken(TC_STI,   "STI",   "0111",             0, &index, opcodeTable);
    initToken(TC_STR,   "STR",   "0111",             0, &index, opcodeTable);
    initToken(TC_TRAP,  "TRAP",  "11110000",         0, &index, opcodeTable);
}


void initRegisterTable(){
    int index = 0;
    initToken(TC_REG,   "R0", "000", 0, &index, registerTable);
    initToken(TC_REG,   "R1", "001", 0, &index, registerTable);
    initToken(TC_REG,   "R2", "010", 0, &index, registerTable);
    initToken(TC_REG,   "R3", "011", 0, &index, registerTable);
    initToken(TC_REG,   "R4", "100", 0, &index, registerTable);
    initToken(TC_REG,   "R5", "101", 0, &index, registerTable);
    initToken(TC_REG,   "R6", "110", 0, &index, registerTable);
    initToken(TC_REG,   "R7", "111", 0, &index, registerTable);
}

void initDirectiveTable(){
    int index = 0;
    initToken(TC_BLKW,    "BLKW",    "", 0, &index, directiveTable);
    initToken(TC_END,     "END",     "", 0, &index, directiveTable);
    initToken(TC_FILL,    "FILL",    "", 0, &index, directiveTable);
    initToken(TC_ORIG,    "ORIG",    "", 0, &index, directiveTable);
    initToken(TC_STRINGZ, "STRINGZ", "", 0, &index, directiveTable);
}

void initScanner(FILE* infile, FILE* outfile){
    initOpcodeTable();
    initRegisterTable();
    initDirectiveTable();
    codeLineNumber = 0;
    codeLineColumn = 0;
    initChario(infile, outfile);
}

int nextInstruction(){
    codeLineColumn = 0;
    codeLine = nextCodeLine();
    if (codeLine != NULL){
        codeLineNumber++;
        return 1;
    }
    else
        return 0;  
}

// Advances one column through the code line and returns the character there.
char nextChar(){
    codeLineColumn++;
    return codeLine[codeLineColumn];
}

int charToInt(int base, char ch){
    if (base == 10)
        if (isdigit(ch))
            return ch - '0';
        else
            putError("Bad decimal digit in integer.");
    else if (! isdigit(ch))
        return toupper(ch) - 'A' + 10;
    else
        return ch - '0';
}
    
// Scans through digits and converts them to a signed int
token getInteger(char ch){
    char sign = '+';
    int base = 10;
    if (ch == 'x')
        base = 16;
    if (ch == 'x' || ch == '#')
        ch = nextChar();
    if (ch == '-'){
        sign = ch;
        ch = nextChar();
    }  
    globalToken.type = TC_INT;
    globalToken.source = "";
    globalToken.binary = "";
    globalToken.intValue = 0;
    do{
        globalToken.intValue = base * globalToken.intValue + charToInt(base, ch);
        ch = nextChar();
    }while (isxdigit(ch));
    if (sign == '-')
        globalToken.intValue = -globalToken.intValue;
}

void getDirective(){
    tokenLength = 0;
    char ch = nextChar();
    while (ch != ' ' && ch != '\t' && ch != '\n'){
        tokenBuffer[tokenLength] = ch;
        tokenLength++;
        ch = nextChar();
    }
    tokenBuffer[tokenLength] = 0;
    makeUppercase(tokenBuffer);
    int index = findToken(tokenBuffer, directiveTable, MAX_DIRECTIVES);
    if (index != -1) 
        globalToken = directiveTable[index];
}

void getRegister(){
    tokenLength = 0;
    char ch = codeLine[codeLineColumn];
    while (ch != ' ' && ch != '\t' && ch != '\n' && ch != ','){
        tokenBuffer[tokenLength] = ch;
        tokenLength++;
        ch = nextChar();
    }
    tokenBuffer[tokenLength] = 0;
    makeUppercase(tokenBuffer);
    int index = findToken(tokenBuffer, registerTable, MAX_REGISTERS);
    if (index != -1) 
        globalToken = registerTable[index];
}

void getOpcode(){
    int index = findToken(tokenBuffer, opcodeTable, MAX_OPCODES);
    if (index != -1) 
        globalToken = opcodeTable[index];
}

void getLabel(){
    globalToken.source = tokenBuffer;
    int index;
    for (index = 0; index < tokenLength - 1; index++)
        if (! isalnum(tokenBuffer[index]))
            return;   
    globalToken.type = TC_LABEL;
}

void getStringLit(){
    tokenLength = 0;
    char ch = nextChar();
    while (ch != '\"' && ch != '\n'){
        tokenBuffer[tokenLength] = ch;
        tokenLength++;
        ch = nextChar();
    }
    tokenBuffer[tokenLength] = 0;
    if (ch != '\"')
        putError("String literal must end in \" before end of line.");
    else
        ch = nextChar();
    globalToken.type = TC_STRING_LIT;
    globalToken.source = copyString(tokenBuffer);
    globalToken.intValue = tokenLength;
}


token nextToken(){
    globalToken.type = TC_ERROR;
    globalToken.source = "";
    globalToken.binary = "";
    globalToken.intValue = 0;
    tokenLength = 0;
    codeLineColumn = skipBlanks(codeLine, codeLineColumn);
    char ch = codeLine[codeLineColumn];
    if (ch == '\n' || ch == ';')
        globalToken.type = TC_NEWLINE;
    else if (ch == ','){
        globalToken.type = TC_COMMA;
        globalToken.source = ",";
        ch = nextChar();
    }
    else if (ch == '.')
        getDirective();
    else if (ch == '\"')
        getStringLit();
    else if (isdigit(ch) || ch == '#' || ch == 'x')
        getInteger(ch);
    else if (! isalpha(ch)){
        globalToken.type = TC_ERROR;
        putError("Unrecognized symbol");
        ch = nextChar();
    }
    else{
        getRegister();
        if (globalToken.type == TC_ERROR){
            getOpcode();
            if (globalToken.type == TC_ERROR)
                getLabel();
        }      
    }
    return globalToken;
}