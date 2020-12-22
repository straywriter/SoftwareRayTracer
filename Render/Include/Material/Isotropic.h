#pragma once
#include   "IMaterial.h"
#include "Texture.h"

class Isotropic : public IMaterial {
    public:
        Isotropic(color c) : albedo(make_shared<SolidColor>(c)) {}
        Isotropic(shared_ptr<Texture> a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const override {
            scattered = Ray(rec.p, random_in_unit_sphere(), r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.p);
            return true;
        }

    public:
        shared_ptr<Texture> albedo;
};