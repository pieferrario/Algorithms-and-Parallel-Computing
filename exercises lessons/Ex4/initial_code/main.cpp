//============================================================================
// Name        : FunctionMin1.cpp
// Author      : Danilo
// Version     :
// Copyright   :
//============================================================================

#include <iostream>

#include "Function.hpp"
#include "FunctionMin.hpp"

using std::cout;
using std::endl;

int main()
{
  Function f ({1., 1., 2., -10., 2.});
  std::cout << "Function: " << std::endl;
  f.print();
  std::cout << "Function: " << f.eval (1) << std::endl;
  FunctionMin minF (f, -1, 4, 1e-3, 1e-3, 1000000);
    double x_min = minF.solve();
  std::cout << "Function minimum at: " << x_min <<", f(x) = " << f.eval(x_min) << std::endl;
    double x_min2 =  minF.solve_multistart (100000);
  std::cout << "Function minimum (multi-start) at: "
            << x_min2 <<", f(x) = " << f.eval(x_min2) << std::endl;
    double x_min3 = minF.solve_domain_decomposition (10, 100000);
  std::cout << "Function minimum (multi-start domain decomp) at: "
            << x_min3 <<", f(x) = " << f.eval(x_min3) << std::endl;

  return 0;
}
