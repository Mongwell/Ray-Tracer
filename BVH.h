#ifndef BVH_H
#define BVH_H

#include "Geometry/Hittable.h"
#include <vector>

using std::vector;

class BVH : public Hittable {
    public:
        BVH();
        BVH(vector<Hittable*>& elems);
        virtual Hittable* clone() const;
        ~BVH();

        virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
        virtual BoundingBox bounds() const;

    private:
        class BVHNode : public Hittable {
            public: 
                BVHNode();
                BVHNode(BoundingBox b);
                virtual Hittable* clone() const;
                virtual ~BVHNode();

                virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
                virtual BoundingBox bounds() const;

                Hittable* left;
                Hittable* right;
                BoundingBox box;
        };

        Hittable* root_;

        Hittable* construct(vector<Hittable*>& elems, vector<Hittable*>::iterator left, 
                vector<Hittable*>::iterator right, unsigned dim);
};

#endif
