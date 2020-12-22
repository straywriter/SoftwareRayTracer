#pragma once

#include "Render.h"

#include "Hit.h"
#include "Rect.h"

/**
 * 
 * 
 */
class Box : public IHitable
{
  public:
    Box()
    {
    }
    Box(const point3 &p0, const point3 &p1, shared_ptr<IMaterial> ptr);

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB &output_box) const override
    {
        output_box = AABB(box_min, box_max);
        return true;
    }

  public:
    point3 box_min;
    point3 box_max;
    HittableList sides;
};

Box::Box(const point3 &p0, const point3 &p1, shared_ptr<IMaterial> ptr)
{
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides.add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    sides.add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides.add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    sides.add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides.add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool Box::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    return sides.hit(r, t_min, t_max, rec);
}
