#ifndef GEOMETRIC_LIST_H
#define GEOMETRIC_LIST_H

#include "geometric.hpp"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class geometric_list : public geometric {
  public:
    geometric_list() {}
    explicit geometric_list(shared_ptr<geometric> ent) { append(ent); }

    void clear() { entities.clear(); }
    void append(shared_ptr<geometric> ent) { entities.push_back(ent); }

    bool intersect(const ray &r, double t_min, double t_max,
                   hit_record *rec) const override;

  public:
    vector<shared_ptr<geometric>> entities;
};

#endif
