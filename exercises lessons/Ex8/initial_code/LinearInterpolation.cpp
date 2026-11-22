#include "LinearInterpolation.h"

LinearInterpolation::LinearInterpolation (const std::vector<Point> & points) : Interpolation(points){};

double
LinearInterpolation::interpolate (double x) const
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
    // given those two points, we have to identify the line connecting them.
    // the angular coefficient is m = (y2-y1)/(x2-x1)

    double angular_coefficient = (points[vector_idx + 1].get_y() - points[vector_idx].get_y())/(points[vector_idx + 1].get_x() - points[vector_idx].get_x());

    return angular_coefficient * (x - points[vector_idx].get_x()) + points[vector_idx].get_y();
}

