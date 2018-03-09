#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Hittable.h"

class Scene : public Hittable {

    public:

        /**
         * Iterates over all Hittables in scene
         * and determines if they are hit by the ray.
         * hit_record will be that of last Hittable hit,
         * i.e., the Hittable on top
         * See Hittable.h
         */
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;

        /**
         * Dtor.
         */
        virtual ~Scene();

        std::vector<Hittable*> scene;

};

#endif
