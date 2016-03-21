/* Author: Ken LambertThis program prints the average of a set of input integers.*/#include <stdio.h>

int main(){
    int sum = 0;    int count = 0;    int number;    printf("Enter a number or 0 to stop: ");    scanf("%d", &number);    while (number){        sum += number;        count++;        printf("Enter a number or 0 to stop: ");        scanf("%d", &number);
    }    if (count > 0)        printf("The average is %f\n", sum / (double) count);    else        printf("No numbers entered\n");}