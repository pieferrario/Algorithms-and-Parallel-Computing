#include "NearestNeighborInterpolation.h"

NearestNeighborInterpolation::NearestNeighborInterpolation (const std::vector<Point> & points) : Interpolation(points) {};

double
NearestNeighborInterpolation::interpolate (double x) const
{
        // first, we check that x is in range
        if (!range_check(x))
        {
            return error_value;
        }

        // if we get here, then x is valid.
        // we have to identify the 2 elements that bind x.
        std::size_t vector_idx = find_extrema(x);

        // we have to check whether x is nearest to a or b.
        if ((x - points[vector_idx].get_x()) < (points[vector_idx + 1].get_x() - x))
        {
            return points[vector_idx].get_y();
        }
        return points[vector_idx + 1].get_y();



}