/*
Author: Leigh Stauffer
Project 10
File: symboltable.c
Implementation for the symbol table module.
*/

//Imported libraries:
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "symboltable.h"


//Type definitions:
typedef struct symbolEntry{
	char* symbol;
	int address;
} symbolEntry;

typedef struct node{
	symbolEntry entry;
	struct node *next;
} node;

typedef node* nodePtr;

nodePtr getNode(symbolEntry entry, nodePtr next);

// The single symbol table.
static nodePtr symbolTable;

// The function implementations go here.

void initSymbolTable(){
	symbolTable = NULL;
}

char* enterSymbol(char* symbol, int address){
	if (findSymbol(symbol) != -1){
		return NULL;}
	else{
		symbolEntry entry;
		entry.symbol = symbol;
		entry.address = address;
		symbolTable = getNode(entry, symbolTable);
		return symbol;}	
}

int findSymbol(char* symbol){
	nodePtr probe = symbolTable;
	while(probe != NULL){
		if(strcmp(symbol, probe->entry.symbol) == 0)
			return probe->entry.address;
		probe = probe->next;
	}
	return -1;
}

void printSymbolTable(){
	nodePtr probe = symbolTable;
	while(probe != NULL){
		printf("%s\t %d\n", probe->entry.symbol, probe->entry.address);
		probe = probe->next;
	}


}

nodePtr getNode(symbolEntry entry, nodePtr next){
	nodePtr ptr = malloc(sizeof(node));
	ptr->entry = entry;
	ptr->next = next;
	return ptr;
}

// They include all of the functions in the interface, as well as
// a getNode helper function.
