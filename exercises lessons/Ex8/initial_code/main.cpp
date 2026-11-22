#include <iostream>

#include "LinearInterpolation.h"
#include "StepwiseInterpolation.h"
#include "NearestNeighborInterpolation.h"

int
main (void)
{
    std::vector<Point> points {
    Point (1.0, 0.0),
      Point (2.0, 3.0),
      Point (3.0, 1.0),
      Point (4.0, 2.0),
      Point (5.0, 4.0)
      };

    //    double x = 2.5;
    double x;
    std::cout << "Insert x: " << std::endl;
    std::cin >> x;

    std::cout << "The selected number is x = " << x << std::endl;

    std::cout << "Linear interpolation" << std::endl;
    LinearInterpolation linear (points);
    double y_linear = linear.interpolate (x);
    std::cout << "Linear: " << y_linear   << std::endl;

    std::cout << "Stepwise interpolation" << std::endl;
    StepwiseInterpolation stepwise (points);
    double y_stepwise = stepwise.interpolate (x);
    std::cout << "Stepwise: " << y_stepwise << std::endl;

    std::cout << "Nearest neighbor interpolation" << std::endl;
    NearestNeighborInterpolation nearest (points);
    double y_nearest  = nearest.interpolate (x);
    std::cout << "Nearest-neighbor: " << y_nearest  << std::endl;



    return 0;
}
