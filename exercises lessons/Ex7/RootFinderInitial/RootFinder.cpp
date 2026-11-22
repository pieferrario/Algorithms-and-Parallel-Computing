/*
 * RootFinder.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "RootFinder.hpp"

bool RootFinder::converged (real increment, real residual) const {
  /*
    Compares a parameter value against desired tolerance.
    The parameter is chosen upon the value of check.
  */

  /* Your code goes here */
  // switch is a chain of else if which chooses the proper case
  switch (termination_criteria)
  {
  case INCREMENT:
    return increment < tolerance;
  case RESIDUAL:
    return residual < tolerance;
  case BOTH:
    return (increment < tolerance) and (residual < tolerance);
  }
}
