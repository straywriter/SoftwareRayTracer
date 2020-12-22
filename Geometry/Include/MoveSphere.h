/**
 * @file MoveSphere.h
 * 
 * @date 2020-12-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include "Render.h"

#include "IHitable.h"
#include "AABB.h"

class MovingSphere : public IHitable
{
  public:
    MovingSphere()
    {
    }
    MovingSphere(point3 cen0, point3 cen1, double _time0, double _time1, double r, shared_ptr<IMaterial> m)
        : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m){};

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    virtual bool bounding_box(double _time0, double _time1, AABB &output_box) const override;

    point3 center(double time) const;

  public:
    point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<IMaterial> mat_ptr;
};

point3 MovingSphere::center(double time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::bounding_box(double _time0, double _time1, AABB &output_box) const
{
    AABB box0(center(_time0) - Vector3d(radius, radius, radius), center(_time0) + Vector3d(radius, radius, radius));
    AABB box1(center(_time1) - Vector3d(radius, radius, radius), center(_time1) + Vector3d(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

bool MovingSphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    Vector3d oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vector3d outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
