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
    // Instead of cycling over the idx we can cycle over the vectors elements

    for (const double & coeff: coefficients)
    {

    }
}

Function Function::derivative() const
{
    std::vector<double> dcoeffs;

    /* YOUR CODE GOES HERE */

    return Function(dcoeffs);
}

void Function::print() const
{
    /* YOUR CODE GOES HERE */
}
