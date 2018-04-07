#include "BVH.h"
#include "BoxCompare.h"
#include <algorithm>

BVH::BVHNode::BVHNode() : left(NULL), right(NULL) {  }

BVH::BVHNode::BVHNode(BoundingBox b) : BVHNode() { box = b; }

Hittable* BVH::BVHNode::clone() const { return NULL; }

BVH::BVHNode::~BVHNode() {
    if (left != NULL) {
        delete left; 
        left = NULL;
    }
    if (right != NULL) {
        delete right;
        right = NULL;
    }
}

bool BVH::BVHNode::hit(const Ray& r, float tmin, float tmax, hit_record& rec) const {
    if (box.hit(r, tmin, tmax)) {
        hit_record leftRec, rightRec;
        bool hitLeft = left ? left->hit(r, tmin, tmax, leftRec) : false;
        bool hitRight = right ? right->hit(r, tmin, tmax, rightRec) : false;

        if (hitLeft && hitRight) rec = leftRec.t < rightRec.t ? leftRec : rightRec;
        else if (hitLeft) rec = leftRec;
        else if (hitRight) rec = rightRec;

        return hitLeft || hitRight;
    }

    return false;
}

BoundingBox BVH::BVHNode::bounds() const { return box; }

BVH::BVH() : root_(NULL) {  }

Hittable* BVH::clone() const { return NULL; }

Hittable* BVH::construct(vector<Hittable*>& elems, vector<Hittable*>::iterator left, 
        vector<Hittable*>::iterator right, unsigned dim) {

    if ((left == right) && (left == elems.end())) return NULL;
    if (left == right) return (*left); 

    BoxCompare comp(dim);
    std::sort(left, right, comp);

    BVHNode* node = new BVHNode();

    node->left = construct(elems, left, left + (right - left) / 2, (dim + 1) % 3);
    node->right = construct(elems, left + (right - left) / 2 + 1, right, (dim + 1) % 3);

    if (node->left && node->right) node->box = (node->left->bounds()) + (node->right->bounds());
    else if (node->left) node->box = node->left->bounds();
    else if (node->right) node->box = node->right->bounds();
    else return NULL;

    return node;
}

BVH::BVH(vector<Hittable*>& elems) {
    root_ = construct(elems, elems.begin(), elems.end(), 0);
}

bool BVH::hit (const Ray& r, float tmin, float tmax, hit_record& rec) const {
    return root_->hit(r, tmin, tmax, rec);
}

BoundingBox BVH::bounds() const { return root_->bounds(); }

BVH::~BVH() {
    if (root_ != NULL) { 
        delete root_;
        root_ = NULL;
    }
}
