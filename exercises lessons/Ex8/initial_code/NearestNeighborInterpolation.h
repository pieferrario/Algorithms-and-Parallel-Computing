#ifndef NEAREST_NEIGHBOR_INTERPOLATION_HH
#define NEAREST_NEIGHBOR_INTERPOLATION_HH

#include <vector>

#include "Interpolation.h"

/* TO BE COMPLETED */

class NearestNeighborInterpolation
{
public:
  explicit NearestNeighborInterpolation (const std::vector<Point> &);

  double interpolate (double) const;
};

#endif // NEAREST_NEIGHBOR_INTERPOLATION_HH
