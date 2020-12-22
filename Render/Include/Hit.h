#pragma once

#include "Render.h"

#include "AABB.h"
#include "IHitable.h"
#include <memory>
#include <vector>

/**
 * hitable list is a
 *
 */
class HittableList : public IHitable
{
  public:
    /** Construct a new hittable list object */
    HittableList()
    {
    }

    /**
     * Construct a new hittable list object
     *
     * @param object
     */
    HittableList(shared_ptr<IHitable> object)
    {
        add(object);
    }

    /**
     * clear
     *
     */
    void clear()
    {
        objects.clear();
    }

    /**
     *
     *
     * @param object
     */
    void add(shared_ptr<IHitable> object)
    {
        objects.push_back(object);
    }

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
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    /**
     *
     *
     * @param time0
     * @param time1
     * @param output_box
     * @return true
     * @return false
     */
    virtual bool bounding_box(double time0, double time1, AABB &output_box) const override;

    /**
     *
     *
     * @param o
     * @param v
     * @return double
     */
    virtual double pdf_value(const Vector3d &o, const Vector3d &v) const override;

    /**
     *
     *
     * @param o
     * @return Vector3d
     */
    virtual Vector3d random(const Vector3d &o) const override;

  public:
    std::vector<shared_ptr<IHitable>> objects;
};

double HittableList::pdf_value(const point3 &o, const Vector3d &v) const
{
    auto weight = 1.0 / objects.size();
    auto sum = 0.0;

    for (const auto &object : objects)
        sum += weight * object->pdf_value(o, v);

    return sum;
}

bool HittableList::bounding_box(double time0, double time1, AABB &output_box) const
{
    if (objects.empty())
        return false;

    AABB temp_box;
    bool first_box = true;

    for (const auto &object : objects)
    {
        if (!object->bounding_box(time0, time1, temp_box))
            return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

bool HittableList::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
    HitRecord temp_rec;
    auto hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

Vector3d HittableList::random(const Vector3d &o) const
{
    auto int_size = static_cast<int>(objects.size());
    return objects[random_int(0, int_size - 1)]->random(o);
}
