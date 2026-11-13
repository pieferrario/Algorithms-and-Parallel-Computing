#ifndef LINEAR_INTERPOLATION_HH
#define LINEAR_INTERPOLATION_HH

#include <vector>

#include "Interpolation.h"

/* TO BE COMPLETED */

class LinearInterpolation
{

public:
  explicit LinearInterpolation (const std::vector<Point> &);

  double interpolate (double) const;
};

#endif // LINEAR_INTERPOLATION_HH
