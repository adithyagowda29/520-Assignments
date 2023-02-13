#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {};

    double magnitude() const;

    //Function to return real part of complex number
    double real() const;
    //Function to return imaginary part of complex number
    double imag() const;
    //Function to return conjugate of the complex number
    Complex conjugate() const;

    //Function to return sum of two complex numbers
    friend Complex operator+(const Complex &a, const Complex &b);
    //Function to return multiplication of two complex numbers
    friend Complex operator*(const Complex &a, const Complex &b);
    //Function to return whether two complex numbers are equal or not
    friend bool operator==(const Complex &a, const Complex &b);

    private:
    double re, im;
}; 

bool operator<(const Complex& a, const Complex& b);

#endif