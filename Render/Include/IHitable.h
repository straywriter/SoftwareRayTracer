#pragma once

#include "Render.h"

class AABB;
class material;

#include "HitRecord.h"

class hittable {
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const = 0;

        virtual double pdf_value(const Vector3d& o, const Vector3d& v) const {
            return 0.0;
        }

        virtual Vector3d random(const Vector3d& o) const {
            return Vector3d(1,0,0);
        }
};
