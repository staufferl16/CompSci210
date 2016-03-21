#include <stdio.h>
#include "tools.h"
#include "chario.h"
#include "token.h"
#include "scanner.h"
#include "symboltable.h"
#include "firstpass.h"

void acceptAddress(int address){
    if (address < DEFAULT_START_ADDRESS)
        putError("Address too low.");
    else if (address > MAX_ADDRESS)
        putError("Address too high.");
}
    
void firstPass(FILE *infile, FILE *outfile){
    initScanner(infile, outfile);
    initSymbolTable();
    int address = DEFAULT_START_ADDRESS;

    // Process the first line, checking for the .ORIG directive
    int moreLines = nextInstruction();
    if (! moreLines){
        putError("No instructions.");
        return;
    }
    token firstToken = nextToken();
    if (firstToken.type = TC_ORIG){
        token beginAddress = nextToken();
        if (beginAddress.type == TC_INT){
            address = beginAddress.intValue - 1;
            acceptAddress(address + 1);
        }
        else
            putError("Integer literal expected.");
    }
    else if (firstToken.type == TC_LABEL){
        char* result = enterSymbol(copyString(firstToken.source), address);
        if (result == NULL)
            putError("Label already declared.");
        else{
            token directive = nextToken();
            printToken(directive);
            if (directive.type == TC_BLKW){
                token size = nextToken();
                if (size.type == TC_INT)
                    address += size.intValue - 1;
                else
                    putError("Integer literal expected.");
            }
            else if (directive.type == TC_STRINGZ){
                token size = nextToken();
                if (size.type == TC_STRING_LIT)
                    address += size.intValue;
                else
                    putError("Integer literal expected.");
            }
        }
    }
    address++;

    // Process the rest of the lines after the first one, or
    // until the first token is .END
    while (moreLines = nextInstruction()){
        firstToken = nextToken();
        if (firstToken.type == TC_END)
            break;
        if (firstToken.type == TC_LABEL){
            char* result = enterSymbol(copyString(firstToken.source), address);
            if (result == NULL)
                putError("Label already declared.");
            else{
                token directive = nextToken();            // Could be a BLKW
                if (directive.type == TC_BLKW){
                    token size = nextToken();
                    if (size.type == TC_INT)
                        address += size.intValue - 1;     // Extra cells for BLKW
                    else
                        putError("Integer literal expected.");
                }
                else if (directive.type == TC_STRINGZ){
                    token size = nextToken();
                    if (size.type == TC_STRING_LIT)
                       address += size.intValue;
                    else
                         putError("Integer literal expected.");
                }
            }
        }
        address++;
    }
} 
