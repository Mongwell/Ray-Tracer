#include <glm/glm.hpp>
#include "Triangle.h"
using namespace glm;

Triangle::Triangle(vec3 point1, vec3 point2, vec3 point3) : v1_(point1), v2_(point2), v3_(point3) {  }

Triangle::~Triangle() {  }

/**
 * Möller–Trumbore triangle intersection algorithm
 * paraphrased from Wikipedia: https://goo.gl/uEUXGn
 */
bool Triangle::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    const float EPSILON = 0.0000001; 

    float a, f, u, v;
    vec3 edge1, edge2, h, s, q;

    edge1 = v2_ - v1_;
    edge2 = v3_ - v1_;
    h = cross(r.direction(), edge2);
    a = dot(edge1, h);

    if (a > -EPSILON && a < EPSILON) return false;

    f = 1/a;
    s = r.origin() - v1_;
    u = f * dot(s, h);

    if (u < 0.0 || u > 1.0) return false;

    q = cross(s, edge1);
    v = f * dot(r.direction(), q);

    if (v < 0.0 || u + v > 1.0) return false;

    float t = f * dot(edge2, q);
    if (t > EPSILON && t < t_max && t > t_min) {
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = cross(normalize(edge1), normalize(edge2));
        return true;
    }
    return false;
}
