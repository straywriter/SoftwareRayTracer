#pragma once

#include "IHitable.h"


class translate : public hittable {
    public:
        translate(shared_ptr<hittable> p, const Vector3d& displacement)
            : ptr(p), offset(displacement) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

    public:
        shared_ptr<hittable> ptr;
        Vector3d offset;
};


bool translate::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    Ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}


bool translate::bounding_box(double time0, double time1, AABB& output_box) const {
    if (!ptr->bounding_box(time0, time1, output_box))
        return false;

    output_box = AABB(
        output_box.min() + offset,
        output_box.max() + offset);

    return true;
}
