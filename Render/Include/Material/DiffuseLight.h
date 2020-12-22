#pragma once
#include "IMaterial.h"
#include "Texture.h"

class DiffuseLight : public IMaterial
{
  public:
    DiffuseLight(shared_ptr<Texture> a) : emit(a)
    {
    }
    DiffuseLight(color c) : emit(make_shared<SolidColor>(c))
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override
    {
        return false;
    }

    virtual color emitted(double u, double v, const point3 &p) const override
    {
        return emit->value(u, v, p);
    }

  public:
    shared_ptr<Texture> emit;
};
