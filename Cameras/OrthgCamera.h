#ifndef ORTHGCAMERA_H
#define ORTHGCAMERA_H
#include "Camera.h"

class OrthgCamera : public Camera {
    public: 
        OrthgCamera();
        virtual Ray get_ray(float u, float v);

    //private:
        glm::vec3 lower_left_corner_;
        glm::vec3 horizontal_;
        glm::vec3 vertical_;
        glm::vec3 direction_;
};

#endif

