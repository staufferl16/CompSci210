/* Author: Ken LambertThis program prints the result of comparing two input strings.*/#include <stdio.h>

int main(){
    char[20] string1, string2;    printf("Enter a string: ");    scanf("%s", string1);    printf("Enter a string: ");    scanf("%s", string2);    printf("%d", string1 == string2);}