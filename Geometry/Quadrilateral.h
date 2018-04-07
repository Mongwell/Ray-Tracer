#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H
#include "Hittable.h"
#include "Triangle.h"

class Quadrilateral : public Hittable {
    public :
        Quadrilateral(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4);
        Quadrilateral(const Quadrilateral& other);
        virtual Hittable* clone() const;
        virtual ~Quadrilateral();

        virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
        virtual BoundingBox bounds() const;

        const Triangle t1;
        const Triangle t2;
};

#endif
