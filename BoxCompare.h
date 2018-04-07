#ifndef BOX_COMPARE_H
#define BOX_COMPARE_H

#include "Geometry/Hittable.h"

class BoxCompare {
    public:
        BoxCompare(int d) : dim(d) {  }
        bool operator()(const Hittable* lhs, const Hittable* rhs) {
            return lhs->bounds().getMin()[dim] < rhs->bounds().getMin()[dim];
        }
    private:
        int dim;
};

#endif
