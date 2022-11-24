#include "vec3.hpp"
#include <cmath>

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

double vec3::length() const { return sqrt(length_squared()); }
