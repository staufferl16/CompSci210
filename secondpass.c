#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tools.h"
#include "chario.h"
#include "token.h"
#include "scanner.h"
#include "symboltable.h"
#include "firstpass.h"
#include "secondpass.h"

#define FILL_ZERO "0000000000000000"
#define SIX_ZEROS "000000"

// Parsing function prototypes
void program();
void instruction();
void orig_ins();
void add_or_and_ins();
void blkw_ins();
void br_ins();
void fill_ins();
void jmp_ins();
void jsr_ins();
void jsrr_ins();
void ld_ldi_st_sti_ins();
void ldr_or_str_ins();
void lea_ins();
void not_ins();
void ret_or_rti_ins();
void stringz_ins();
void trap_ins();

// Module variables
static int spAddress;
static int spNotDone;
static token spToken;
static FILE* binfile;
static char outputBuffer[17];

// Outputs the binary instruction to the .bin file
void outputBinary(){
    fputs(outputBuffer, binfile);
    fputs("\n", binfile);
}

// Handles error when token is unexepcted
void accept(tokenType expectedType, char* errorMessage){
    if (expectedType != spToken.type)
        putError(errorMessage);
}

// Converts an integer to a signed bit string and 
// appends that to the output buffer
void processLabel(int numBits){
    accept(TC_LABEL, "Label expected.");
    if (spToken.type == TC_LABEL){
        int labelAddress = findSymbol(spToken.source);
        if (labelAddress == -1)
            putError("Undeclared label.");
        else{
            int offset = labelAddress - (spAddress + 1);
            strcat(outputBuffer, signedBinary(offset, numBits));
        }
    }
}

// The purported end of an instruction has been reached, so
// check for the newline, get the next instruction, get 
//  its first token, and increment the address counter.
void finishInstruction(){
    spToken = nextToken();
    accept(TC_NEWLINE, "Too many tokens in instruction.");
    spNotDone = nextInstruction();
    if (spNotDone){
        spAddress++;
        spToken = nextToken();
    }
}
    
// Initializes the data, gets the first instruction, and gets
// first token
void secondPass(FILE* infile, FILE* outfile, FILE* bfile){
    binfile = bfile;
    outputBuffer[16] = 0;
    initScanner(infile, outfile);
    spAddress = DEFAULT_START_ADDRESS;
    spNotDone = nextInstruction();
    spToken = nextToken();
    program();
}

void program(){
    orig_ins();
    while (spNotDone && spToken.type != TC_END)
        instruction();
    accept(TC_END, ".END expected.");
}

void orig_ins(){
    if (spToken.type = TC_ORIG){
        spToken = nextToken();                // First pass guarantees an int here
        spAddress = spToken.intValue - 1;
        spToken = nextToken();
        finishInstruction();
    }
    strcpy(outputBuffer, unsignedBinary(spAddress, 16));
    outputBinary();
}

void add_or_and_ins(){    
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_COMMA, "Comma expected.");
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_COMMA, "Comma expected.");
    spToken = nextToken();
    if (spToken.type == TC_REG){
        strcat(outputBuffer, "000");
        strcat(outputBuffer, spToken.binary);
    }
    else if (spToken.type == TC_INT){
        strcat(outputBuffer, "1");
        if (spToken.intValue < -16 || spToken.intValue > 15)
            putError("Integer literal too large or too small.");
        else
            strcat(outputBuffer, signedBinary(spToken.intValue, 5));
    }
    else
        putError("Register or immediate operand expected.");
    outputBinary();
    finishInstruction();
}

void blkw_ins(){
    strcpy(outputBuffer, FILL_ZERO);
    spToken = nextToken();
    accept(TC_INT, "Integer literal expected.");
    int i;
    for (i = 1; i <= spToken.intValue; i++)
        outputBinary();
    spAddress += spToken.intValue - 1;
    finishInstruction();
}

void br_ins(){
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    processLabel(9);
    outputBinary();
    finishInstruction();
}

void fill_ins(){
    spToken = nextToken();
    accept(TC_INT, "Integer literal expected.");
    strcpy(outputBuffer, signedBinary(spToken.intValue, 16));
    outputBinary();
    finishInstruction();
}

void jmp_ins(){
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    strcat(outputBuffer, SIX_ZEROS);
    outputBinary();
    finishInstruction();
}

void jsr_ins(){
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    processLabel(11);
    outputBinary();
    finishInstruction();
}

void jsrr_ins(){
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    strcat(outputBuffer, SIX_ZEROS);
    outputBinary();
    finishInstruction();
}

void ld_ldi_lea_st_sti_ins(){
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_COMMA, "Comma expected.");
    spToken = nextToken();
    processLabel(9);
    outputBinary();
    finishInstruction();
}

void ldr_or_str_ins(){
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_COMMA, "Comma expected.");
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_COMMA, "Comma expected.");
    spToken = nextToken();
    accept(TC_INT, "Integer literal expected.");
    if (spToken.intValue < -32 || spToken.intValue > 31)
        putError("Integer literal too large or too small.");
    else
        strcat(outputBuffer, signedBinary(spToken.intValue, 6));
    outputBinary();
    finishInstruction();
}

void not_ins(){    
    strcpy(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    spToken = nextToken();
    accept(TC_COMMA, "Comma expected.");
    spToken = nextToken();
    accept(TC_REG, "Register expected.");
    strcat(outputBuffer, spToken.binary);
    outputBinary();
    finishInstruction();
}

void ret_or_rti_ins(){
    strcpy(outputBuffer, spToken.binary);
    outputBinary();
    finishInstruction();
}

void stringz_ins(){
    spToken = nextToken();
    accept(TC_STRING_LIT, "String literal expected.");
    char* lit = spToken.source;
    int i;
    for (i = 0; i < spToken.intValue; i++){
        char ch = lit[i];
        strcpy(outputBuffer, unsignedBinary(ch, 16));
        outputBinary();
    }
    strcpy(outputBuffer, FILL_ZERO);
    outputBinary();
    spAddress += spToken.intValue - 2;            
    finishInstruction();
}

void trap_ins(){
    strcpy(outputBuffer, spToken.binary);
    if (spToken.type == TC_TRAP){
        spToken = nextToken();
        accept(TC_INT, "Trap vector expected.");
        strcat(outputBuffer, unsignedBinary(spToken.intValue, 12));
    }
    outputBinary();
    finishInstruction();
}

void instruction(){
    if (spToken.type == TC_LABEL)
        spToken = nextToken();
    switch (spToken.type){
        case TC_ADD     : 
        case TC_AND     : add_or_and_ins();
                          break; 
        case TC_BLKW    : blkw_ins();
                          break; 
        case TC_BR      : 
        case TC_BRZ     : 
        case TC_BRN     : 
        case TC_BRP     : 
        case TC_BRNZ    : 
        case TC_BRZP    : 
        case TC_BRNZP   : 
        case TC_BRNP    : br_ins();
                          break; 
        case TC_FILL    : fill_ins();
                          break; 
        case TC_JMP     : jmp_ins();
                          break; 
        case TC_JSR     : jsr_ins();
                          break; 
        case TC_JSRR    : jsrr_ins();
                          break; 
        case TC_LD      : 
        case TC_LDI     :
        case TC_LEA     : 
        case TC_ST      : 
        case TC_STI     : ld_ldi_lea_st_sti_ins();
                          break; 
        case TC_LDR     : 
        case TC_STR     : ldr_or_str_ins();
                          break; 
        case TC_NOT     : not_ins();
                          break; 
        case TC_RET     :  
        case TC_RTI     : ret_or_rti_ins();
                          break; 
        case TC_STRINGZ : stringz_ins();
                          break; 
        case TC_GETC    : 
        case TC_HALT    : 
        case TC_IN      : 
        case TC_OUT     : 
        case TC_PUTS    : 
        case TC_TRAP    : trap_ins();
                          break;
        case TC_ERROR   : break;
        default         : putError("Unrecognized symbol.");
                          break;
    }
}

/* 


    else if (firstToken.type == TC_LABEL){
        char* result = enterSymbol(copyString(firstToken.source), address);
        if (result == NULL)
            putError("Label already declared.");
        else{
            token directive = nextToken();
            if (directive.type == TC_BLKW){
                token size = nextToken();
                if (size.type == TC_INT)
                    address += size.intValue - 2;
                else
                    putError("Integer literal expected.");
            }
        }
    }
    address++;

    // Process the rest of the lines after the first one.
    while (moreLines = nextInstruction()){
        firstToken = nextToken();
        if (firstToken.type == TC_LABEL){
            char* result = enterSymbol(copyString(firstToken.source), address);
            if (result == NULL)
                putError("Label already declared.");
            else{
                token directive = nextToken();            // Could be a BLKW
                if (directive.type == TC_BLKW){
                    token size = nextToken();
                    if (size.type == TC_INT)
                        address += size.intValue - 2;     // Extra cells for BLKW
                    else
                        putError("Integer literal expected.");
                }
            }
        }
        address++;
    }
} 

*/
