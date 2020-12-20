#pragma once

#include "Render.h"

class aabb;
class material;

#include "HitRecord.h"

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

        virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;

        virtual double pdf_value(const vec3& o, const vec3& v) const {
            return 0.0;
        }

        virtual vec3 random(const vec3& o) const {
            return vec3(1,0,0);
        }
};
