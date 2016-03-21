/* Author: Ken LambertThis program prints the amount of interest.*/#include <stdio.h>

#define INTEREST_RATE .06int main(){
    double principal = 10000.00;
    printf("Interest is %.2f\n",
           INTEREST_RATE * principal);}