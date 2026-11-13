#ifndef STEPWISE_INTERPOLATION_HH
#define STEPWISE_INTERPOLATION_HH

#include <vector>

#include "Interpolation.h"

/* TO BE COMPLETED */

class StepwiseInterpolation
{
public:
  explicit StepwiseInterpolation (const std::vector<Point> &);

  double interpolate (double) const;
};

#endif // STEPWISE_INTERPOLATION_HH
