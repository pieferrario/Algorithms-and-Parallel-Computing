/*
 * Function.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include <cmath>

#include "Function.hpp"

double Function::eval (double x) const
{
    double result = 0.0;
    /*
     for (std::size_t idx = 0; idx < coefficients.size(); ++idx)
    {
        result += coefficients[idx] * std::pow(x, idx);
    }
    */
    // Instead of cycling over the idx we can cycle over the member of the vector

    double x_power = 1;
    for (const double & coeff: coefficients)
    {
        result += coeff * x_power;
        x_power *= x; // This is more efficient than using pow;
    }
    return result;
}

Function Function::derivative() const
{
    std::vector<double> dcoeffs; // We have to build a vector of coefficients for the derivative

    for (std::size_t k = 0; k < coefficients.size() -1; ++k)
    {
        dcoeffs.push_back((k+1)*coefficients[k+1]);
    }

    return Function(dcoeffs);
}

void Function::print() const
{
    // we want to print somthing like f(x) = a_0 + a_1 x + ... + a_n x^n;
    std::cout << "f(x) = " << coefficients[0];
    for (std::size_t k = 1; k < coefficients.size(); ++k)
    {
        std::cout << " + " << coefficients[k] << " x^" << k;
    }
    std::cout << std::endl;
}
