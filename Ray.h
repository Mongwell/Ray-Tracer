#ifndef RAY_H
#define RAY_H
#include <glm/vec3.hpp>

class Ray {
    public: 
        /**
         * Default ctor.
         */
        Ray();

        /**
         * Standard ctor.
         */
        Ray(const glm::vec3& a, glm::vec3& b);

        /**
         * Getter for start of ray.
         * @return copy of start_
         */
        glm::vec3 origin() const;

        /**Getter for direction vector of ray.
         * @return copy of direction_
         */
        glm::vec3 direction() const;

        /**
         * Parametrically locates a point on the ray.
         * @param t parameter
         * @return point on the ray
         */
        glm::vec3 point_at_parameter(float t);

    private:
        glm::vec3 start_;
        glm::vec3 direction_;
};

#endif
