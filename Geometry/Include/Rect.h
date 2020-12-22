#pragma once

#include "Render.h"

#include "IHitable.h"

class XYRect : public IHitable
{
  public:
    XYRect()
    {
    }

    XYRect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<IMaterial> mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat){};

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB &output_box) const override
    {
        // The bounding box must have non-zero width in each dimension, so pad the Z
        // dimension a small amount.
        output_box = AABB(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
        return true;
    }

  public:
    shared_ptr<IMaterial> mp;
    double x0, x1, y0, y1, k;
};

class XZRect : public IHitable
{
  public:
    XZRect()
    {
    }

    XZRect(double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<IMaterial> mat)
        : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat){};

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB &output_box) const override
    {
        // The bounding box must have non-zero width in each dimension, so pad the Y
        // dimension a small amount.
        output_box = AABB(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
        return true;
    }

  public:
    shared_ptr<IMaterial> mp;
    double x0, x1, z0, z1, k;
};

class YZRect : public IHitable
{
  public:
    YZRect()
    {
    }

    YZRect(double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<IMaterial> mat)
        : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat){};

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB &output_box) const override
    {
        // The bounding box must have non-zero width in each dimension, so pad the X
        // dimension a small amount.
        output_box = AABB(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
        return true;
    }

  public:
    shared_ptr<IMaterial> mp;
    double y0, y1, z0, z1, k;
};

bool XYRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    auto t = (k - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    auto outward_normal = Vector3d(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);

    return true;
}

bool XZRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    auto t = (k - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vector3d(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);

    return true;
}

bool YZRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    auto t = (k - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;

    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;

    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vector3d(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);

    return true;
}