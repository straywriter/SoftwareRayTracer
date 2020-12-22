#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

/**
 *
 *
 * @param degrees
 * @return double
 */
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

/**
 *
 *
 * @param x
 * @param min
 * @param max
 * @return double
 */
inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

/**
 *
 *
 * @return double
 */
inline double random_double()
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

/**
 *
 *
 * @param min
 * @param max
 * @return double
 */
inline double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

/**
 * return a random integer in [min,max]
 *
 * @param min
 * @param max
 * @return int
 */
inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max + 1));
}

#include "Ray.h"
#include "Vector3d.h"
