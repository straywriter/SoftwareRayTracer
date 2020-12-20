#pragma once
#include "IMaterial.h"


//TODO



class lambertianT : public material {
    public:
        lambertianT(const color& a) : albedo(make_shared<solid_color>(a)) {}
        lambertianT(shared_ptr<texture> a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered
        ) const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = Ray(rec.p, scatter_direction, r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.p);
            return true;
        }

    public:
        shared_ptr<texture> albedo;
};
