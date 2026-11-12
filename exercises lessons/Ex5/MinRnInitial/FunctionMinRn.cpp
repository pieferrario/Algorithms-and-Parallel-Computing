#include <cmath>
#include <iostream>
#include <random>

#include "FunctionMinRn.h"
#include "FunctionRn.h"
#include "Monomial.h"

Point FunctionMinRn::solve (const Point & P) const  // Gradient descent formula in Rn: x_k+1 = x_k - \alpha grad(f(x_k));
{
    Point P0(P.get_coords());
    double f0 = f.eval(P0);

    bool converged = false;

    for (unsigned int i = 0; i < max_iterations and ! converged; ++i)
    {
        for (std::size_t j = 0; j < P0.get_n_dimensions(); ++j)  // we compute the formula by component
        {
            const double grad_j = f.eval_deriv(j, P0);
            double x_new = P0.get_coord(j) - step * grad_j;

            if (grad_j > 0)
                x_new = std::max (inf_limits[j], x_new);
            else
                x_new = std::min (sup_limits[j], x_new);
        // Now we update the coordinate through a proper setter:
        P0.set_coord(j, x_new);
        }
        // We compute again the first steps for the updated point:
        double f1 = f.eval(P0);
        Point grad = compute_gradient(P0);

        // we update the converged condition:
        converged = (std::abs(f1-f0) < tolerance) or (grad.infinity_norm() < tolerance);

        f0 = f1;
    }

  return P0;
}

Point FunctionMinRn::solve (void) const
{
  std::vector<double> initial_coords;

  //compute domain mid point
  for (std::size_t i = 0; i < sup_limits.size (); ++i)
    initial_coords.push_back ((sup_limits[i] + inf_limits[i]) / 2);
  const Point P (initial_coords);

  return solve (P);
}

// gradient descent with multi-start
Point FunctionMinRn::solve_multistart (unsigned int n_trials) const
{
  // first we import a random engine
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution (0, 1);
    std::vector<double> random_coords;

  // and generate random coordinates using an uniform distribution in [0,1]
    for (size_t idx = 0; idx < inf_limits.size(); ++idx)
    {
        const double rand_val = distribution (generator);
        random_coords.push_back (inf_limits[idx] + (sup_limits[idx] - inf_limits[idx]) * rand_val);
    }

  // then we create a random starting point
    Point random_point = Point(random_coords);

  // and get a first guess of solution
    Point p_min = solve(random_point);

  // now we loop on n_iterations to find the best solution
    for (unsigned j = 0; j < n_trials - 1; ++j){
        for (size_t idx = 0; idx < inf_limits.size(); ++idx)
        {
            const double rand_val = distribution(generator);
            random_coords[idx] = (inf_limits[idx] + (sup_limits[idx]-inf_limits[idx]) * rand_val);
        }

        random_point = Point(random_coords);

        const Point p_new = solve(random_point);
        if (f.eval (p_new) < f.eval (p_min))
        p_min = p_new;
    }
return p_min;
}

// gradient descent with multi-start and domain decomposition
Point FunctionMinRn::solve_domain_decomposition (unsigned int n_intervals,
                                                 unsigned int n_trials) const
{
  std::vector<double> internal_steps;
  // compute steps along each axis
  for (std::size_t i = 0; i < inf_limits.size(); ++i)
    internal_steps.push_back ((sup_limits[i] - inf_limits[i]) / n_intervals);

  Point p_min = Point(inf_limits);
  const unsigned int n_subspaces = pow (n_intervals, inf_limits.size ());

  std::vector<double> cur_inf_limit (inf_limits);
  for (unsigned int i = 1; i <= n_subspaces; ++i)
  {
    // compute cur_sup_limits
    std::vector<double> cur_sup_limit;
    for (std::size_t j = 0; j < cur_inf_limit.size (); ++j)
      cur_sup_limit.push_back (cur_inf_limit[j] + internal_steps[j]);
    FunctionMinRn minf_int (f,  tolerance,  step, max_iterations,
                              cur_inf_limit, cur_sup_limit);

    const Point p_iter = minf_int.solve_multistart (n_trials);
    if (f.eval (p_iter) < f.eval (p_min))   // keep the best result so far
      p_min = p_iter;

    next_inf_limit (cur_inf_limit, internal_steps);   // move to the next sub-box
  }
    return p_min;
  }


  void FunctionMinRn::next_inf_limit (std::vector<double> & cur_inf_limit,
                                      const std::vector<double> & internal_steps) const
  {
    for (std::size_t j = 0; j < cur_inf_limit.size (); ++j)
    {
      if (cur_inf_limit[j] + internal_steps[j] >= sup_limits[j])
      {
        cur_inf_limit[j] = inf_limits[j];
      }
      else
      {
        cur_inf_limit[j] += internal_steps[j];

        return;
      }
    }
  }



Point FunctionMinRn::compute_gradient (const Point & P0) const
{
    std::vector<double> derivative_values;
    for (size_t j = 0; j < P0.get_n_dimensions(); ++j)
    {
        derivative_values.push_back(f.eval_deriv(j, P0));
    }
    return Point(derivative_values);
}

void FunctionMinRn::debug_info (const std::string& s) const
{
  if (debug)
    std::cout << s << " " << std::endl;
}

void FunctionMinRn::debug_info (const std::string& s, double val) const
{
  if (debug)
    std::cout << s << " " << val << std::endl;
}
