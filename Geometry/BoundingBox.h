#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/vec3.hpp>
#include "../Ray.h"

class BoundingBox {
    public :
        BoundingBox();
        BoundingBox(const glm::vec3& a, const glm::vec3& b);

        glm::vec3 getMin();
        glm::vec3 getMax();

        bool hit (const Ray& r, float t_min, float t_max) const;

        BoundingBox operator+(const BoundingBox& rhs);

    private :
        glm::vec3 min_;
        glm::vec3 max_;
};

#endif
