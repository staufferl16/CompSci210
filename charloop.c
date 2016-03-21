/* Author: Ken LambertThis program prints the uppercase letters.*/#include <stdio.h>

int main(){
    char aLetter;
    for (aLetter = 'A'; aLetter <= 'Z'; aLetter++)
        putchar(aLetter);
    putchar('\n');}