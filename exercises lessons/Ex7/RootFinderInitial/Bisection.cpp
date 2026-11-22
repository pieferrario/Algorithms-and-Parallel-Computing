/*
 * Bisection.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Bisection.hpp"

#include <iostream>
#include <cmath>
#include <cstdlib>

real Bisection::find_root(int &nit) const {

    real a = inf_limit;
    real b = sup_limit;
    real f_a = func.eval(a);
    real c = (a+b)/2;
    real f_c = func.eval(c);

    bool conv_check = converged(std::abs(c-a), std::abs(f_c));
    unsigned current_it = 1;

    while (current_it < max_iteration and !conv_check)
    {
        // Bisection step
        if (f_a * f_c < 0)
        {
            // We consider the left interval
            b = c;
        }
        else
        {
            // We consider the right interval
            a = c;
            f_a = f_c;
        }

        c = (a+b)/2;
        f_c = func.eval(c);

        conv_check = converged(std::abs(c-a), std::abs(f_c));
        ++current_it;
    }

    nit = current_it;
  return c;
}
