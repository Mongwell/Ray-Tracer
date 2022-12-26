#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "../ray.hpp"

struct hit_record {
    point3 p;
    vec3 norm;
    double t;
};

class geometric {
  public:
    virtual bool intersect(const ray &r, double t_min, double t_max,
                           hit_record *rec) const = 0;
    virtual vec3 unit_surface_norm(const point3 p) const = 0;
};

#endif
