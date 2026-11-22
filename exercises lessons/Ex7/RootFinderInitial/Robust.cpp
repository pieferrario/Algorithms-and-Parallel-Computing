/*
 * Robust.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Robust.hpp"

real Robust::find_root(int &nit_bis, int &nit_newt) const {

  Bisection bis(func, inf_limit, sup_limit, tolerance*cratio, termination_criteria, max_iteration);

  real x_init = bis.find_root(nit_bis);

    Newton nw(func, x_init, tolerance, termination_criteria, max_iteration);

  real x_final = nw.find_root(nit_newt);

  return x_final;
}


