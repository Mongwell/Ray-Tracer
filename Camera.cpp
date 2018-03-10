#include "Camera.h"
using glm::vec3;

Camera::Camera() : lower_left_corner_(vec3(-2.0, -1.0, -1.0)), horizontal_(vec3(4.0, 0.0, 0.0)), vertical_(vec3(0.0, 2.0, 0.0)), origin_(vec3(0.0, 0.0, 0.0)) {  }

Ray Camera::get_ray(float u, float v) {
    vec3 direction = lower_left_corner_ + u*horizontal_ + v*vertical_ - origin_;
    return Ray(origin_, direction);
}
