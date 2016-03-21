/* Author: Ken LambertThis program prints some numeric data.*/#include <stdio.h>

int main(){
    int anInt = 97;    double aDouble = 4.56;    char aLetter = 'A';     printf("%d %.2f %d", anInt, aDouble, aLetter);   // Outputs 97 4.56 65
    putchar(aLetter);
    putchar('\n');}