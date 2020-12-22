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

/**
 * hitable object record
 */
struct HitRecord
{
    point3 p;                      //< point 3 position
    Vector3d normal;               //<
    shared_ptr<IMaterial> mat_ptr; //<
    double t;                      //<
    double u;                      //<
    double v;                      //<
    bool front_face;               //<

    /**
     * Set the face normal object
     *
     * @param r
     * @param outward_normal
     */
    inline void set_face_normal(const Ray &r, const Vector3d &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};