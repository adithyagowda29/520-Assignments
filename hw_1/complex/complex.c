#include <math.h>
#include "complex.h"

//Function to add two complex numbers
Complex add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.im = a.im + b.im;
    return result;
}

//Function to negate a complex number
Complex negate(Complex a) {
    Complex result;
    result.real = -a.real;
    result.im = -a.im;
    return result;
}

//Function to multiply two complex numbers
Complex multiply(Complex a, Complex b) {
    Complex result;
    result.real = (a.real * b.real) - (a.im * b.im);
    result.im = (a.real * b.im) + (a.im * b.real);
    return result;
}

//Function to calculate magnitude of a complex number
double magnitude(Complex a) {
    return (double)sqrt((a.real * a.real) + (a.im * a.im));
}