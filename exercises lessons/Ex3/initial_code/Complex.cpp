//
// Created by pietr on 08/10/2026.
//

#include "Complex.h"
// Constructor

double Complex::get_real() const
{
    return real;
}
double Complex::get_img() const
{
    return imaginary;
}
double Complex::get_modulus() const
{
    return sqrt(pow(real, 2) + pow(imaginary,2));
}
double Complex::get_phase() const
{
    if (real > 0)
        return atan(imaginary/real);
    if (real < 0 and imaginary >= 0)
        return atan(imaginary/real) + M_PI;
    if (real < 0 and imaginary < 0)
        return atan(imaginary/real) - M_PI;
    if (real == 0 and imaginary > 0 )
        return M_PI/2;
    if (real == 0 and imaginary < 0)
        return - M_PI/2;
    if (real == 0 and imaginary == 0)
    {
        std::cerr << "Undefined phase" << std::endl;
        return 0;
    }
    return 0;
}

void Complex::set_real(double real)
{
    this->real = real;
}

void Complex::set_img(double imaginary)
{
    this->imaginary = imaginary;
}

void Complex::set_modulus(double modulus)
{
    double phase = get_phase();
    real = modulus * cos(phase);
    imaginary = modulus * sin(phase);
}

void Complex::set_phase(double phase)
{
    double modulus = get_modulus();
    real = modulus * cos(phase);
    imaginary = modulus * sin(phase);
}

// Helper functions
void Complex::print() const
{
    std::cout << real << "+" << imaginary << "i" << std::endl;
}

void Complex::print_polar() const
{
    std::cout << get_modulus() << "[cos(" << get_phase() * 180 / M_PI << ") + i sin(" << get_phase() * 180 / M_PI << ")]" << std::endl;
}


Complex operator+(const Complex & lhs, const Complex & rhs)
{
    return Complex(lhs.get_real() + rhs.get_real(), lhs.get_img()+ rhs.get_img());
}
Complex operator-(const Complex & lhs, const Complex & rhs)
{
    return Complex(lhs.get_real() - rhs.get_real(), lhs.get_img() - rhs.get_img());
}

Complex operator*(const Complex & lhs, const Complex & rhs)
{
    double new_real = lhs.get_real() * rhs.get_real() - lhs.get_img() * rhs.get_img();
    double new_imaginary = lhs.get_img() * rhs.get_real() + lhs.get_real() * rhs.get_img();
    return Complex(new_real, new_imaginary);
}

Complex operator/(const Complex & lhs, const Complex & rhs) {
    double den = pow(rhs.get_modulus(),2);
    double real_new = (lhs.get_real()*rhs.get_real() + lhs.get_img()*rhs.get_img()) / den;
    double img_new = (rhs.get_real()*lhs.get_img() - rhs.get_img()*lhs.get_real()) / den;
    return Complex(real_new, img_new);
}
