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
  bool converged = false;

  // until we converge or we reach max iterations....
  for (size_t i = 0; i < max_iterations && ! converged; ++i)
  {
      // evaluate derivative
      double df_eval = df.eval(x0); // f'(x_{i-1})

      // compute next point
      double x1 = x0 - step * df_eval; // x_i = x_{i-1} - \delta * f'(x_{i-1})

      if (x1 < inf_limit)
      {
          x1 = inf_limit;
      }
      if (x1 > sup_limit)
      {
          x1 = sup_limit;
      }

      // compute new function value
      double f1 = f.eval(x1);

      // check convergence
      // | x_1 - x_0 | < tol or |f(x1) - f(x0)| < tol or |f'(x0)| < tol
      if (std::abs(x1 - x0) < tolerance or std::abs(f1 - f0) < tolerance or std::abs(df.eval(x1)) < tolerance)
      {
          converged = true;
      }

      // reassign the variables
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

    double x_min = solve(); // Solve uses as initial value the midpoint of the interval
    double f_min = f.eval(x_min);

    for (unsigned n = 1; n < n_trials; ++n)
    {
        const double x_guess = distribution(generator);  // that's a callable object
        // run gradient descent with x_guess as initial point
        double x_new = solve(x_guess);
        double f_new = f.eval(x_new);

        if (f_new < f_min)
        {
            x_min = x_new;
            f_min = f_new;
        }
    }
    return x_min;
}

// gradient descent with multi-start and domain decomposition
double FunctionMin::solve_domain_decomposition (unsigned n_intervals,
                                                unsigned n_trials) const
{
  double x_min;
    double f_min = std::numeric_limits<double>::max();
    // length = (b-a) / n_intervals
    // every interval is [a + length * idx, a + length * (idx + 1)]
    // first interval: [a, a + length]
    // last interval: [a + length * (n_intervals-1), b]
  double length = (sup_limit - inf_limit) / n_intervals;
    for ( std::size_t idx = 0; idx < n_intervals; ++idx)
    {
        FunctionMin subproblem(
            f,
            inf_limit + length*idx,
            inf_limit + length * (idx + 1),
            tolerance,
            step,
            max_iterations);
     double x_new = subproblem.solve_multistart(n_trials);
     double f_new = f.eval(x_new);
        if (f_new < f_min)
        {
            x_min = x_new;
            f_min = f_new;
        }
    }
  return x_min;
}
