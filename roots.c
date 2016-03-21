/* Author: Ken LambertThis program prints the roots of quadratic equation with input 
coefficients a, b, and c.*/

#include <stdio.h>#include <math.h>
void quadraticRoots(float a, float b, float c,                     float *root1, float *root2);

int main(){    // double a = 30.3, b = 30.2, c = 4.1, root1, root2;
    float a, b, c, root1, root2;
    printf("Enter a, b, and c: ");
    scanf("%f%f%f", &a, &b, &c);    quadraticRoots(a, b, c, &root1, &root2);    printf("Root1: %f\n", root1);    printf("Root2: %f\n", root2);}void quadraticRoots(float a, float b, float c,                     float *root1, float *root2){    *root1 = - b + sqrt(b * b - 4 * a * c) / (2 * a);    *root2 = - b - sqrt(b * b - 4 * a * c) / (2 * a);}