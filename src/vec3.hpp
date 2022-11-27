#ifndef VEC3_H
#define VEC3_H

#include <ostream>

struct pixel {
    char r;
    char g;
    char b;
};
typedef pixel pixel;

class vec3 {
  private:
    double data[3];

  public:
    // Constructors
    vec3() : data{0, 0, 0} {}
    vec3(double v0, double v1, double v2) : data{v0, v1, v2} {}

    // Accessors
    double x() const { return data[0]; }
    double y() const { return data[1]; }
    double z() const { return data[2]; }

    double r() const { return data[0]; }
    double g() const { return data[1]; }
    double b() const { return data[2]; }

    double operator[](int i) const;

    // Manipulators
    double &operator[](int i);

    // Math
    vec3 operator-() const;

    vec3 &operator+=(const vec3 &v);
    vec3 &operator*=(const double m);
    vec3 &operator/=(const double d);

    double sum() const;
    double length_squared() const;
    double length() const;

    pixel to_pixel() const;
};

// Type aliases
using point3 = vec3;
using color = vec3;

// Utility Functions //
std::ostream &operator<<(std::ostream &out, const vec3 &v);
vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, const vec3 &v);
vec3 operator*(const double t, const vec3 &v);
vec3 operator*(const vec3 &v, const double t);
vec3 operator/(const vec3 &v, double t);
double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 unit_vector(const vec3 &v);

#endif
