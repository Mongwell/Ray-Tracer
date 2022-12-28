#ifndef RT_COMMON_H
#define RT_COMMON_H

#include <cmath>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

//// Utility Functions ////

inline double degrees_to_radians(double deg) { return deg * M_PI / 180.0; }

#include "ray.hpp"
#include "vec3.hpp"

#endif
