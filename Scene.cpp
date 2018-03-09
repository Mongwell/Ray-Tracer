#include "Scene.h"

bool Scene::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record tempRec;
    bool hitAnything = false;
    double closestSoFar = t_max;

    for (const Hittable* h : scene) {
        if (h->hit(r, t_min, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

Scene::~Scene() {
    for (Hittable* h: scene) {
        if (h != NULL) {
            delete h;
            h = NULL;
        }
    }
}
