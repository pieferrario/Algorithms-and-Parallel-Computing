#ifndef INTERPOLATION_HH
#define INTERPOLATION_HH

#include <vector>
#include <limits>

#include "Point.h"

class Interpolation
{
protected:
  std::vector<Point> points; // sorted_vector
  // We must return NaN when a point does not belong to the domain.
  // The error value is stored as a protected class constant:
  //  - constexpr: compile-time constant (implicitly const).
  //  - static: one copy shared by the class; also required, since
  //    non-static data members cannot be constexpr.
  //  - std::numeric_limits<double>::quiet_NaN(): C++ has no NaN literal;
  // In the following we can easily use error_value.
  constexpr static double error_value = std::numeric_limits<double>::quiet_NaN();

public:
  virtual double interpolate (double) const = 0; // interpolate is an abstract class method

  // we develop a range check function to be sure that the element is in the domain
  bool range_check(double number) const; // it is const since it can't modify the number
  std::size_t find_extrema(double x) const; // we add a method to find the extrema of the shortest interval a <= x <= b given the vector of points.

  // constructor and virtual default destructor
  Interpolation(const std::vector<Point> & points);
  virtual ~Interpolation(void) = default;
};

#endif // INTERPOLATION_HH
