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
class hittable_list : public hittable
{
  public:
    /** Construct a new hittable list object */
    hittable_list()
    {
    }

    /**
     * Construct a new hittable list object
     *
     * @param object
     */
    hittable_list(shared_ptr<hittable> object)
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
    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;
    
    virtual double pdf_value(const vec3 &o, const vec3 &v) const override;

    virtual vec3 random(const vec3 &o) const override;

  public:
    std::vector<shared_ptr<hittable>> objects;
};

double hittable_list::pdf_value(const point3 &o, const vec3 &v) const
{
    auto weight = 1.0 / objects.size();
    auto sum = 0.0;

    for (const auto &object : objects)
        sum += weight * object->pdf_value(o, v);

    return sum;
}

bool hittable_list::bounding_box(double time0, double time1, aabb &output_box) const
{
    if (objects.empty())
        return false;

    aabb temp_box;
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

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
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

vec3 hittable_list::random(const vec3 &o) const
{
    auto int_size = static_cast<int>(objects.size());
    return objects[random_int(0, int_size - 1)]->random(o);
}