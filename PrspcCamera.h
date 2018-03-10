#ifndef PRSPCCAMERA_H
#define PRSPCCAMERA_H
#include "Camera.h"

class PrspcCamera : public Camera {
    public: 
        PrspcCamera();
        virtual Ray get_ray(float u, float v);

    private:
        glm::vec3 lower_left_corner_;
        glm::vec3 horizontal_;
        glm::vec3 vertical_;
        glm::vec3 origin_;
};

#endif
