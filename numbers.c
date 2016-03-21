/*
* Author: Leigh Stauffer
* File Name: numbers.c
* Homework 8
* Implementation file for numbers program.  Takes user inputs, puts inputs
* into an array, finds their sum, and finds their average.
*/

#include "numbers.h"
#include <stdio.h>

int getNumbers(int numbers[], int max){
/* Gets user inputs.  Max is the maxium logical size of the array. Numbers *  is the array of user inputted numbers. Returns the number of inputs.*/
	int count = 0;
	int number;
	printf("Enter a number or 0 to stop: ");
	scanf("%d", &number);
	while(number){
		numbers[count] = number;
		count++;
		if (count == max){
			printf("Maxium number of inputs exceeded.");
			break;}
		printf("Enter a number or 0 to stop: ");
		scanf("%d", &number);
	}
	return count;
}	

int sum(int numbers [], int count){
/* Sums the user input numbers.  Count is the number of user input numbers.*/
	int total = 0;
	int index;
	for (index = 0; index < count; index++)
		total += numbers[index];
	return total;
}

float average(int numbers[], int count){
/* Averages the user input numbers. Count is, again, the number ofuser input
* numbers.*/
	float newSum = sum (numbers, count);
	return newSum/count;
}

void printNumbers(int numbers[], int count){
/* Prints the answers from all the methods.*/
	int index;
	for(index = 0; index < count; index++){
		printf("%d\n", numbers[index]);
		}
	
}


