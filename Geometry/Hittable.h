#ifndef HITTABLE_H
#define HITTABLE_H

#include "../Ray.h"
#include "BoundingBox.h"

struct hit_record {
    /**
     * ray paramter for hit
     */
    float t;

    /**
     * point of ray contact on hittable
     */
    glm::vec3 p;

    /**
     * normal vector on hittable at point of contact
     */
    glm::vec3 normal;
};

class BoundingBox;

class Hittable {
    public:

        /**
         * Determine if Ray r will hit this object in a parameter range
         * @param r Ray to check for hit
         * @param t_min minimum parameter value
         * @param t_max maximum parameter value
         * @param rec struct to write hit data to
         * @return if object was hit
         */
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
        virtual BoundingBox bounds() const = 0;

        virtual Hittable* clone() const = 0;
        /**
         * Dtor.
         */
        virtual ~Hittable() {  };
};


#endif
