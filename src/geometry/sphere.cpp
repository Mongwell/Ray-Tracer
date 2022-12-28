#include "sphere.hpp"
#include <cmath>

using std::sqrt;

bool sphere::intersect(const ray &r, double t_min, double t_max,
                       hit_record *rec) const {
    // check if ray hits sphere using quadratic formula discriminant
    vec3 c2o = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(c2o, r.direction());
    double c = c2o.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return false;
    }

    // Find nearest root in acceptable t range
    double sqrtd = sqrt(discriminant);
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec->t = root;
    rec->p = r.at(rec->t);
    rec->set_face_norm(r, out_unorm(rec->p));

    return true;
}

vec3 sphere::out_unorm(const point3 p) const {
    return (p - center) / radius;
}
