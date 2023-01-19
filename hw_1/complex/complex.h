#ifndef COMPLEX_H
#define COMPLEX_H

//Structure to define complex numbers
typedef struct {
    double real;
    double im;
} Complex;

//Define functions for operations on complex numbers
Complex add(Complex a, Complex b);
Complex negate(Complex a);
Complex multiply(Complex a, Complex b);
double magnitude(Complex a);

#endif