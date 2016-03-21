/* Author: Ken LambertThis program prints the area of a circle, given its input radius. 
*/#include <stdio.h>#define PI 3.1416

double area(double r);int main(){    float radius;    printf("Enter the radius: ");    scanf("%f", &radius);    printf("The area is %f\n", area(radius));}double area(double r){    return PI * r * r;} 

