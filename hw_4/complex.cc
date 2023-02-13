#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

//Function to return real part of complex number
double Complex::real() const {
    return re;
}

//Function to return imaginary part of complex number
double Complex::imag() const {
    return im;
}

//Function to return conjugate of the complex number
Complex Complex::conjugate() const {
    return Complex(re, -im);
}

//Function to return sum of two complex numbers
Complex operator+(const Complex &a, const Complex &b) {
    return Complex(a.re + b.re, a.im + b.im);
}

//Function to return multiplication of two complex numbers
Complex operator*(const Complex &a, const Complex &b) {
    return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

//Function to return whether two complex numbers are equal or not
bool operator==(const Complex &a, const Complex &b) {
    return (a.re == b.re) && (a.im == b.im);
}