#ifndef SPHERE_H
#define SPHERE_H

#include "geometric.hpp"

class sphere : public geometric {
  public:
    sphere() {}
    sphere(point3 c, double r) : center(c), radius(r) {}

    bool intersect(const ray &r, double t_min, double t_max,
                   hit_record *rec) const override;
    vec3 unit_surface_norm(const point3 p) const;

  public:
    point3 center;
    double radius;
};

#endif
