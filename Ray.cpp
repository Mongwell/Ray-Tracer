#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const glm::vec3& a, glm::vec3& b) {
    start_ = a;
    direction_ = b;
}

glm::vec3 Ray::origin() const {
    return start_;
}

glm::vec3 Ray::direction() const {
    return direction_;
}

glm::vec3 Ray::point_at_parameter(float t) {
    return start_ + t * direction_;
}
