#ifndef SPHERE_H
#define SPHERE_H
#include "Hittable.h"

class Sphere : public Hittable {
    public:
        
        /**
         * Standard ctor.
         */
        Sphere(glm::vec3 cen, float r);

        /**
         * Dtor.
         */
        virtual ~Sphere();

        /**
         * Determine if the ray hits this sphere.
         * See Hittable.h
         */
        virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;

        const glm::vec3 center;
        const float radius;
};

#endif
