#ifndef LINEAR_INTERPOLATION_HH
#define LINEAR_INTERPOLATION_HH

#include <vector>

#include "Interpolation.h"

// Linear interpolation is a public derived class from Interpolation
class LinearInterpolation : public Interpolation
{
public:
  explicit LinearInterpolation (const std::vector<Point> &);
  // since it is an inherited class, we have to specify that we are overriding the interpolate method.
  double interpolate (double x) const override;
};

#endif // LINEAR_INTERPOLATION_HH
