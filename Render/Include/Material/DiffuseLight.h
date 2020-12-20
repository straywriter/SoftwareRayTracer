#pragma once
#include "IMaterial.h"
#include "Texture.h"

class diffuse_light : public material
{
  public:
    diffuse_light(shared_ptr<texture> a) : emit(a)
    {
    }
    diffuse_light(color c) : emit(make_shared<solid_color>(c))
    {
    }

    virtual bool scatter(const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered) const override
    {
        return false;
    }

    virtual color emitted(double u, double v, const point3 &p) const override
    {
        return emit->value(u, v, p);
    }

  public:
    shared_ptr<texture> emit;
};
