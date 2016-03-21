/*
Author: Ken Lambert
File: symboltable.h
Interface for the symbol table module.
The application can have only one symbol table. 
*/

// Create an empty table.
void initTable();

// Attempts to enter a symbol and its address.
// If the symbol is already in the table, simply returns NULL.
// Otherwise, enters the symbol and its address and returns the symbol. 
char* enterSymbol(char* symbol, int address);

// Looks up the symbol in the table.
// If the symbol is in the table, returns its address.
// Otherwise, returns -1.
int findSymbol(char* symbol);

// Prints the contents of the table in two columns.
void printSymbolTable();