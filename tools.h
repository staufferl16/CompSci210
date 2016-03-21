// File: tools.h

// Returns the position of the first non-blank character in line,
// starting from position startPos.
int skipBlanks(char* line, int startPos);

// Converts buffer to uppercase
void makeUppercase(char buffer[]);

// Like strcpy, but creates storage for and returns the new string.
char* copyString(char originalString[]);

// Allocates storage for and returns the unsigned
// binary number with length numBits.
char* unsignedBinary(int number, int numBits);

// Allocates storage for and returns the signed
// binary number with length numBits.
char* signedBinary(int number, int numBits);
