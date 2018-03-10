#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"

class Camera {
    public: 
        virtual Ray get_ray(float u, float v) = 0;
};

#endif
