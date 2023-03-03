/**

@file complex_operations.c
@brief This file contains functions for operations on complex numbers.
*/
#include <math.h>

/**
@brief Structure to define complex numbers
*/
typedef struct {
double real; 
double im;
} Complex;
/**

@brief Function to add two complex numbers
@param a First complex number
@param b Second complex number
@return The sum of the two complex numbers
*/
Complex add(Complex a, Complex b){
Complex result;
result.real = a.real + b.real;
result.im = a.im + b.im;
return result;
}
/**

@brief Function to negate a complex number
@param a The complex number to be negated
@return The negated complex number
*/
Complex negate(Complex a){
Complex result;
result.real = -a.real;
result.im = -a.im;
return result;
}
/**

@brief Function to multiply two complex numbers
@param a First complex number
@param b Second complex number
@return The product of the two complex numbers
*/
Complex multiply(Complex a, Complex b){
Complex result;
result.real = (a.real * b.real) - (a.im * b.im);
result.im = (a.real * b.im) + (a.im * b.real);
return result;
}
/**

@brief Function to calculate the magnitude of a complex number
@param a The complex number
@return The magnitude of the complex number
*/
double magnitude(Complex a){
return sqrt((a.real * a.real) + (a.im * a.im));
}
/**

@mainpage Complex Operations
This program defines a structure for complex numbers and provides functions to perform various
operations on them, such as addition, multiplication, negation and calculating magnitude.
@section Dependencies
This program depends on the math.h library.
@section Usage
To use this program, simply include the complex_operations.c file in your project and call the
desired functions as needed.
*/