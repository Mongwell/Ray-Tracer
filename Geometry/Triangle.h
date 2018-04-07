#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Hittable.h"

class Triangle : public Hittable {
    public:

        Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
        Triangle(const Triangle& other);
        virtual Hittable* clone() const;
        virtual ~Triangle();

        /**
         * Möller–Trumbore triangle intersection algorithm
         * paraphrased from Wikipedia: https://goo.gl/uEUXGn
         */
        virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
        virtual BoundingBox bounds() const;

    private:
        glm::vec3* vertices_;
};

#endif
