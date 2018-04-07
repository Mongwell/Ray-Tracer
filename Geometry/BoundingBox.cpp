#include "BoundingBox.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

using glm::vec3;

BoundingBox::BoundingBox() {  }

BoundingBox::BoundingBox(const vec3& a, const vec3& b) : min_(a), max_(b) {  }

vec3 BoundingBox::getMin() { return min_; }
vec3 BoundingBox::getMax() { return max_; }

BoundingBox BoundingBox::operator+(const BoundingBox& rhs) {
    vec3 min;
    vec3 max;
    for (unsigned count = 0; count < 2; ++count) {
        min[count] = rhs.min_[count] < this->min_[count] ? rhs.min_[count] : this->min_[count];
        max[count] = rhs.max_[count] > this->max_[count] ? rhs.max_[count] : this->max_[count];
    }

    return BoundingBox(min, max);
}

bool BoundingBox::hit(const Ray& r, float t_min, float t_max) const {
    for (int count = 0; count < 3; ++count) {
        float t0 = ffmin((min_[count] - r.origin()[count]) / r.direction()[count],
                    (max_[count] - r.origin()[count]) / r.direction()[count]);
        float t1 = ffmax((min_[count] - r.origin()[count]) / r.direction()[count],
                    (max_[count] - r.origin()[count]) / r.direction()[count]);

        t_min = ffmax(t0, t_min);
        t_max = ffmax(t1, t_max);

        //std::cout << t_min << " " << t_max << std::endl;
        if (t_max <=  t_min) return false;
    }

    return true;
}
