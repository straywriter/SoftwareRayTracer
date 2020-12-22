#pragma once
#include "IMaterial.h"


class Lambertian : public IMaterial
{
  public:
    Lambertian(const color &a) : albedo(a)
    {
    }

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        // scattered = ray(rec.p, scatter_direction);
         scattered = Ray(rec.p, scatter_direction, r_in.time());//
        attenuation = albedo;
        return true;
    }

  public:
    color albedo;
};