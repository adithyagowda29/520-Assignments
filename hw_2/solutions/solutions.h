#ifndef SOLUTION_H
#define SOLUTION_H

// 1. Function to compute running total of an argument being called
int running_total(int x);
// 2. Function to return reversed array using calloc
int* reverse(int* x, int len);
// 3. Function to return reversed array in-place
void reverse_in_place(int* x, int len);
// 4. Function to number of occurences of a value in the array
int num_occurences(int* x, int len, int value);

#endif