/*
 * Author: Leigh Stauffer
 * File Name: numbers.h
 * Homework 8
 * Header file for numbers.c. */


int getNumbers(int numbers[], int max);
/* Gets user inputs.  Max is the maxium logical size of the array. Numbers is the
* array of user inputted numbers.*/

int sum(int numbers[], int count);
/* Sums the user input numbers.  Count is the number of user input numbers.*/

float average(int numbers[], int count);
/* Averages the user input numbers. Count is, again, the number ofuser input
* numbers.*/

void printNumbers(int numbers[], int count);
/* Prints the sum and the averages of the input numbers.*/
