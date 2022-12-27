#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "../ray.hpp"

struct hit_record {
    point3 p;
    vec3 norm;
    double t;

    inline void copy_rec(const hit_record &other) {
        p = other.p;
        norm = other.norm;
        t = other.t;
    }
};

class geometric {
  public:
    virtual bool intersect(const ray &r, double t_min, double t_max,
                           hit_record *rec) const = 0;
};

#endif
