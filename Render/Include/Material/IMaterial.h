/**
 * @file IMaterial.h
 *
 * @date 2020-12-18
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once

#include "Render.h"

struct HitRecord;

/**
 *
 *
 */
class IMaterial
{
  public:
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const = 0;


  virtual color emitted(double u, double v, const point3& p) const {
            return color(0,0,0);
        }
        
//TODO: ???

    // virtual color emitted(const ray &r_in, const hit_record &rec, double u, double v, const point3 &p) const
    // {
    //     return color(0, 0, 0);
    // }

    // virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const
    // {
    //     return false;
    // }

    virtual double scattering_pdf(const Ray &r_in, const HitRecord &rec, const Ray &scattered) const
    {
        return 0;
    }
};
