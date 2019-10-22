#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

/**
 * Records
 *      t: the parameter value where a hitable has been hit
 *      p: the point_at_parameter(t)
 *      normal: the normal at the hit point
 */
struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
