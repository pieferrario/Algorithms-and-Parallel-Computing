#include "Interpolation.h"

bool Interpolation::range_check(double number) const
{
    double inf_number = points[0].get_x();
    double sup_number = (points.end() - 1) -> get_x();
    if (inf_number > number or sup_number < number)
    {
        return false;
    }
    return true;
}

std::size_t Interpolation::find_extrema(double x) const
{
double inf_x = points[0].get_x();
double sup_x = points[1].get_x();
std::size_t vector_idx = 0;
for (std::size_t idx = 1; idx < points.size() - 1; ++idx)
{
    if ((x >= inf_x and x <= sup_x))
    {
        break;
    }
        inf_x = sup_x;
        sup_x = points[idx + 1].get_x();
        vector_idx++; // this unsigned counts the index of the first element of the interval in the vector.
}
    return vector_idx;
}

Interpolation::Interpolation(const std::vector<Point> & points): points(points){};
