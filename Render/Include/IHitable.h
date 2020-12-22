#pragma once

#include "Render.h"

class AABB;
class IMaterial;

#include "HitRecord.h"

/**
 * interface of hitabel object
 */
class IHitable
{
  public:
    /**
     *
     *
     * @param r
     * @param t_min
     * @param t_max
     * @param rec
     * @return true
     * @return false
     */
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;

    /**
     *
     *
     * @param time0
     * @param time1
     * @param output_box
     * @return true
     * @return false
     */
    virtual bool bounding_box(double time0, double time1, AABB &output_box) const = 0;

    /**
     *
     *
     * @param o
     * @param v
     * @return double
     */
    virtual double pdf_value(const Vector3d &o, const Vector3d &v) const
    {
        return 0.0;
    }

    /**
     *
     *
     * @param o
     * @return Vector3d
     */
    virtual Vector3d random(const Vector3d &o) const
    {
        return Vector3d(1, 0, 0);
    }
};
