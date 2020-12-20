#pragma once

#include "IMaterial.h"


class metal : public material
{
  public:
   metal(const color& a) : albedo(a) {}

    metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1)
    {
    }

    virtual bool scatter(const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered) const override
    {
        Vector3d reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        // scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere(), r_in.time());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

  public:
    color albedo;
    double fuzz;
};