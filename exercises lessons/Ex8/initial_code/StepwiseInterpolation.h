#ifndef STEPWISE_INTERPOLATION_HH
#define STEPWISE_INTERPOLATION_HH

#include <vector>

#include "Interpolation.h"

class StepwiseInterpolation : public Interpolation
{
public:
  explicit StepwiseInterpolation (const std::vector<Point> &);

  double interpolate (double) const override; // we override because interpolate is a method of the base class
};

#endif // STEPWISE_INTERPOLATION_HH
