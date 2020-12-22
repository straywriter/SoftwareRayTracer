#pragma once
#include "IMaterial.h"

// TODO

class LambertianTexture : public IMaterial
{
  public:
    LambertianTexture(const color &a) : albedo(make_shared<SolidColor>(a))
    {
    }
    LambertianTexture(shared_ptr<Texture> a) : albedo(a)
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

  public:
    shared_ptr<Texture> albedo;
};
