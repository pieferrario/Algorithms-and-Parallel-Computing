#include <algorithm>
#include <cmath>
#include <random>

#include "FunctionMin.hpp"

//gradient descent with x_init initial point
double FunctionMin::solve (double x_init) const
{
  Function df = f.derivative();

  double x0 = x_init;
  double f0 = f.eval(x0);

  // check convergence
  bool converged = /* YOUR CODE GOES HERE */

  // until we converge or we reach max iterations....
  for (size_t i = 0; i < max_iterations && ! converged; ++i)
  {
      // evaluate derivative
      
      /* YOUR CODE GOES HERE */

      // compute next point
      
      /* YOUR CODE GOES HERE */

      // compute new function value
      
      /* YOUR CODE GOES HERE */

      // check convergence
      
      /* YOUR CODE GOES HERE */

      x0 = x1;
      f0 = f1;
  }

  return x0;
}

// gradient descent
double FunctionMin::solve (void) const
{
    double x_min;

    x_min= solve((inf_limit + sup_limit) / 2);

    return x_min;
}

// gradient descent with multi-start
double FunctionMin::solve_multistart (unsigned n_trials) const
{
    std::default_random_engine generator(4850);
    std::uniform_real_distribution<double> distribution (inf_limit,
                                                         sup_limit);

    double x_min = solve();
    double fmin = f.eval(x_min);

    for (unsigned n = 1; n < n_trials; ++n)
    {
        const double x_guess = distribution(generator);  // that's a callable object

        /* YOUR CODE GOES HERE */
    }

    return x_min;
}

// gradient descent with multi-start and domain decomposition
double FunctionMin::solve_domain_decomposition (unsigned n_intervals,
                                                unsigned n_trials) const
{
  double x_min;
  
  /* YOUR CODE GOES HERE */

  return x_min;
}
