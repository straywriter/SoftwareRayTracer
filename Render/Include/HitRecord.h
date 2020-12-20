/**
 * @file HitRecord.h
 *
 * @date 2020-12-18
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Render.h"
#include "Vector3d.h"

struct hit_record
{
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const ray &r, const vec3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};