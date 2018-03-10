#include <glm/glm.hpp>
#include "OrthgCamera.h"
using glm::vec3;

OrthgCamera::OrthgCamera() : lower_left_corner_(vec3(-2.0, -1.0, -1.0)), horizontal_(vec3(4.0, 0.0, 0.0)), vertical_(vec3(0.0, 2.0, 0.0)), direction_(normalize(cross(horizontal_, vertical_))) { 
}

Ray OrthgCamera::get_ray(float u, float v) {
    return Ray(lower_left_corner_ + u*horizontal_ + v*vertical_, direction_);
}
