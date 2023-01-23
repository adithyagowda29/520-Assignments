#include "solutions.h"
#include <stdlib.h>

// 1. Function to compute running total of an argument being called
int running_total(int x) {
    static int total = 0;
    total += x;
    return total;
}

// 2. Function to return reversed array using calloc
int* reverse(int* x, int len){
    int* y = (int*) calloc(len, sizeof(int));
    for (int i = 0; i < len; i++) {
        y[i] = x[len-1-i];
    }
    return y;
}

// 3. Function to return reversed array in-place
void reverse_in_place(int* x, int len) {
    for (int i = 0; i < len/2; i++) {
        int temp = x[i];
        x[i] = x[len-1-i];
        x[len-1-i] = temp;
    }
}

// 4. Function to number of occurences of a value in the array
int num_occurences(int* x, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (x[i] == value) {
            count++;
        }
    }
    return count;
}
