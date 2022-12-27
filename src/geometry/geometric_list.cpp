#include "geometric_list.hpp"

bool geometric_list::intersect(const ray &r, double t_min, double t_max,
                               hit_record *rec) const {
    hit_record current_rec;
    bool hit_anything = false;
    double current_closest = t_max;

    for (const shared_ptr<geometric>& e : entities) {
        if (e->intersect(r, t_min, current_closest, &current_rec)) {
            hit_anything = true;
            current_closest = current_rec.t;
            rec->copy_rec(current_rec);
        }
    }

    return hit_anything;
}
