// File: chario.h

#define MAX_COLUMNS 81

void initChario(FILE* infile, FILE* outfile);

// Returns NULL if the end of file has been reached
// Otherwise, returns the next line of code, after skipping any
// leading blank lines or comments.
char* nextCodeLine();

int getTotalErrors();

void putError(char* errorMessage);

void reportErrors();

