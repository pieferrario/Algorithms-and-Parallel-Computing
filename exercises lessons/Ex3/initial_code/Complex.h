//
// Created by pietr on 08/10/2026.
//

#ifndef INITIAL_CODE_COMPLEX_H
#define INITIAL_CODE_COMPLEX_H
#include<cmath>
#include<iostream>

class Complex
{
private:
    double real, imaginary;
public:
    Complex(double real, double imaginary) : real(real), imaginary(imaginary){}
    // Getters and setters

    double get_real() const;
    double get_img() const;
    double get_modulus() const;
    double get_phase() const;

    void set_real(double);
    void set_img(double);

    void set_modulus(double);
    void set_phase(double);

    // Helper functions
    void print() const;
    void print_polar() const;
};

// These functions are outside of the class, thus we don't need to specify Complex::
Complex operator+(const Complex & lhs, const Complex & rhs);
Complex operator-(const Complex & lhs, const Complex & rhs);
Complex operator*(const Complex & lhs, const Complex & rhs);
Complex operator/(const Complex & lhs, const Complex & rhs);

#endif //INITIAL_CODE_COMPLEX_H
