#include <glm/glm.hpp>
#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4) : t1(Triangle(point1, point2, point3)), t2(Triangle(point3, point2, point4)) {  }

Quadrilateral::~Quadrilateral() {  }

bool Quadrilateral::hit(const Ray& r, float tmin, float tmax, hit_record& rec) const {
    hit_record rec1;
    hit_record rec2;

    bool hit1 = t1.hit(r, tmin, tmax, rec1);
    bool hit2 = t2.hit(r, tmin, tmax, rec2);

    if (!hit1 && !hit2) return false;

    if (!hit2) {
        rec = rec1;
        return true;
    }

    if (!hit1) {
        rec = rec2;
        return true;
    }

    if (rec1.t <= rec2.t) rec = rec1;
    else rec = rec2;

    return true;
}
