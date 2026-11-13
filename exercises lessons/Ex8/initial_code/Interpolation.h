#ifndef INTERPOLATION_HH
#define INTERPOLATION_HH

#include <vector>

#include "Point.h"

class Interpolation
{
   /* TO BE COMPLETED */
protected:
  std::vector<Point> points; // sorted_vector

public:
  virtual double interpolate (double) const = 0;
};

#endif // INTERPOLATION_HH
