#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "../ray.hpp"

struct hit_record {
    point3 p;
    vec3 norm;
    double t;
    bool front_face;

    void copy_rec(const hit_record &other) {
        p = other.p;
        norm = other.norm;
        t = other.t;
    }

    void set_face_norm(const ray& r, const vec3& out_norm) {
        front_face = dot(r.direction(), out_norm) < 0;
        norm = front_face ? out_norm : -out_norm;
    }
};

class geometric {
  public:
    virtual bool intersect(const ray &r, double t_min, double t_max,
                           hit_record *rec) const = 0;
};

#endif
