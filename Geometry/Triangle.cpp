#include <glm/glm.hpp>
#include "Triangle.h"
#include <iterator>
using namespace glm;

Triangle::Triangle(vec3 point1, vec3 point2, vec3 point3) : vertices_(new vec3[3]{point1, point2, point3}) {  }

Triangle::Triangle(const Triangle& other) {
    vertices_ = new vec3[3];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            vertices_[i][j] = other.vertices_[i][j];
        }
    }
}

Hittable* Triangle::clone() const {
    return new Triangle(*this);
}

Triangle::~Triangle() {
    if (vertices_ != NULL) {
        delete[] vertices_;
        vertices_ = NULL;
    }
}

BoundingBox Triangle::bounds() const {
    vec3 min = vertices_[0];
    vec3 max = vertices_[0];

    for (unsigned count = 0; count < 3; ++count) {
        min.x = vertices_[count].x < min.x ? vertices_[count].x : min.x;
        min.y = vertices_[count].y < min.y ? vertices_[count].y : min.y;
        min.z = vertices_[count].z < min.z ? vertices_[count].z : min.z;

        max.x = vertices_[count].x > max.x ? vertices_[count].x : max.x;
        max.y = vertices_[count].y > max.y ? vertices_[count].y : max.y;
        max.z = vertices_[count].z > max.z ? vertices_[count].z : max.z;
    }

    return BoundingBox(min, max);
}

/**
 * Möller–Trumbore triangle intersection algorithm
 * paraphrased from Wikipedia: https://goo.gl/uEUXGn
 */
bool Triangle::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    const float EPSILON = 0.0000001; 

    float a, f, u, v;
    vec3 edge1, edge2, h, s, q;

    edge1 = vertices_[1] - vertices_[0];
    edge2 = vertices_[2] - vertices_[0];
    h = cross(r.direction(), edge2);
    a = dot(edge1, h);

    if (a > -EPSILON && a < EPSILON) return false;

    f = 1/a;
    s = r.origin() - vertices_[0];
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
