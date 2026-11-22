/*
 * Newton.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Newton.hpp"

real Newton::find_root(int &nit) const {

    unsigned curr_it = 0;

    real x_curr = x_init;
    real f_x_curr = func.eval(x_curr);

    real x_new;
    // real f_x_new;

    bool conv_check = converged(tolerance + 1, std::abs(f_x_curr));

    while (curr_it < max_iteration and !conv_check)
    {
        x_new = x_curr - f_x_curr / der.eval(x_curr);
        f_x_curr = func.eval(x_new);
        conv_check = converged(std::abs(x_new - x_curr),f_x_curr);
        ++curr_it;
        x_curr = x_new;
        // f_x_curr = f_x_new;

    }
    nit = curr_it;
  return x_curr;
}
