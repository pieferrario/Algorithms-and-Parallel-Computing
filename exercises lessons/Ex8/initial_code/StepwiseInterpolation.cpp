#include "StepwiseInterpolation.h"

StepwiseInterpolation::StepwiseInterpolation (const std::vector<Point> & points) : Interpolation(points){};

double
StepwiseInterpolation::interpolate (double x) const
{
    // first, we check that x is in range
    if (!range_check(x))
    {
        return error_value;
    }

    // if we get here, then x is valid.
    // we have to identify the 2 elements that bind x.
    std::size_t vector_idx = find_extrema(x);

    // now we have identified a, b s.t x in [a,b] and [a,b] is the shortest interval.
    // then the interpolated y is the y component points[vector_idx]
    // if x coincides with the right extreme, return that point's y
    if (x == points[vector_idx + 1].get_x())
    {
        return points[vector_idx + 1].get_y();
    }
    return points[vector_idx].get_y();
}
