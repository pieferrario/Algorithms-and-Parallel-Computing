#include "FunctionRn.h"

double FunctionRn::eval (const Point & P) const
{
    // We loop on each component of the polynomial and call, for each monomial the function eval. in the end, we sum all the evaluations
    double evaluation = 0.0;
    for (std::size_t it = 0; it < monoms.size(); ++it)
    {
        evaluation += monoms[it].eval(P);
    }
    return evaluation;
}

void FunctionRn::addMonomial (const Monomial & m)
{
  monoms.push_back (m);
}

//evaluate derivative wrt dim j in P
double FunctionRn::eval_deriv (std::size_t j,
                               const Point & P) const
{
     // Since we are in Rn, we are computing a partial derivative.
    // Thus we can use a stable centered finite differences to tackle the evaluation of the derivative in P.
    // This also explains why we have initialised h as static constexpr
    // The general formula for the derivative computation in x is (f(x+h)-f(x-h))/2h
    Point P1(P.get_coords());
    Point P2(P.get_coords());

    P1.set_coord(j, P.get_coord(j)+h);
    P2.set_coord(j, P.get_coord(j)-h);

    return (eval(P1) - eval(P2))/(2*h);
}
