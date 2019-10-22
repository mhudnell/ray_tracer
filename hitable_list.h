#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"
#include <vector>
#include <iostream>

class hitable_list : public hitable {
    public:
        std::vector<hitable*> list;

        hitable_list() {}
        hitable_list(const std::vector<hitable*>& list) : list(list) {}

        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(int i = 0; i < list.size(); i++) {
        hit_record temp_rec;
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif
