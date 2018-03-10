#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"

class Camera {
    public: 
        Camera();
        Ray get_ray(float u, float v);

    private:
        glm::vec3 lower_left_corner_;
        glm::vec3 horizontal_;
        glm::vec3 vertical_;
        glm::vec3 origin_;
};

#endif
