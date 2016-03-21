/* 
Author: Ken Lambert
Implementation file for factorial and gcd functions. 
*/

#include "mylib.h"

int factorial(int n){
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}     int gcd(int a, int b){
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}