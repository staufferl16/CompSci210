/* Author: Ken LambertThis program prints the numbers from an input number down to 0.*/

# include <stdio.h>

# define STOP 0

int main(){

    int counter;
    int startPoint;

    printf("===== Countdown Program =====\n");
    printf("Enter a positive integer: ");
    scanf("%d", &startPoint);
    for (counter = startPoint; counter >= STOP; counter--)
        printf("%d\n", counter);
}