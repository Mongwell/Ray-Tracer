#include "vec3.hpp"
#include <cmath>

using std::ostream;
using std::sqrt;

double vec3::operator[](int i) const { return data[i]; }

double &vec3::operator[](int i) { return data[i]; }

vec3 vec3::operator-() const { return vec3(-data[0], -data[1], -data[2]); }

vec3 &vec3::operator+=(const vec3 &v) {
    data[0] += v.data[0];
    data[1] += v.data[1];
    data[2] += v.data[2];
    return *this;
}

vec3 &vec3::operator*=(const double m) {
    data[0] *= m;
    data[1] *= m;
    data[2] *= m;
    return *this;
}

vec3 &vec3::operator/=(const double d) { return *this *= 1 / d; }

double vec3::length_squared() const {
    return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

double vec3::sum() const { return data[0] + data[1] + data[2]; }

double vec3::length() const { return sqrt(length_squared()); }

pixel vec3::to_pixel() const {
    return {static_cast<char>(data[0] * 255.999),
            static_cast<char>(data[1] * 255.999),
            static_cast<char>(data[2] * 255.999)};
}

// Utility Functions Definitions //

ostream &operator<<(ostream &out, const vec3 &v) {
    return out << v[0] << ", " << v[1] << ", " << v[2];
}

vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

vec3 operator*(const double t, const vec3 &v) {
    return vec3(t * v[0], t * v[1], t * v[2]);
}

vec3 operator*(const vec3 &v, const double t) { return t * v; }

vec3 operator/(const vec3 &v, double t) { return (1 / t) * v; }

double dot(const vec3 &u, const vec3 &v) { return (u * v).sum(); }

vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

vec3 unit_vector(const vec3 &v) { return v / v.length(); }
