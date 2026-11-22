#include "Centroid.h"

void
Centroid::update_coords (std::vector<Point *> const & ps);
{
    std::vector<double> new_coords(x.size(), 0);

    // We have to loop on all points and compute the weighted sum of all points passed as parameters (pointers to points).
    for (size_t i = 0; i < ps.size(); ++i)
    {
        for (size_t j = 0; j < new_coords.size(); ++j)
        {
            // Add the coordinate j of point i to new_coordinates[j];
            new_coords[j] += ps[i]->get_coord(j); // we can't access to the protected member point -> we have to rely on the getters.
        }
    }
    for (size_t j = 0; j < new_coords.size(); ++j)
    {
        new_coords[j] /= ps.size();
    }
    x.swap(new_coords);
}
