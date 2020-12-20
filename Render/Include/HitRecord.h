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
    Vector3d normal;
    shared_ptr<material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const Ray &r, const Vector3d &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};