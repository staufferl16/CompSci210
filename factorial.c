/* This program prints factorial of 6. */#include <stdio.h>

int factorial(int n);int main(){    printf("The factorial of 6 is %d\n", factorial(6));}

int factorial(int n){    if (n == 1)        return 1;    else        return n * factorial(n - 1);}