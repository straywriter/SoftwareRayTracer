#pragma once
#include "IHitable.h"


class FlipFace : public IHitable {
    public:
        FlipFace(shared_ptr<IHitable> p) : ptr(p) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec) const override {

            if (!ptr->hit(r, t_min, t_max, rec))
                return false;

            rec.front_face = !rec.front_face;
            return true;
        }

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
            return ptr->bounding_box(time0, time1, output_box);
        }

    public:
        shared_ptr<IHitable> ptr;
};


class FlipFace : public IHitable {
    public:
        FlipFace(shared_ptr<IHitable> p) : ptr(p) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec) const override {

            if (!ptr->hit(r, t_min, t_max, rec))
                return false;

            rec.front_face = !rec.front_face;
            return true;
        }

        virtual bool bounding_box(double time0, double time1, AABB& output_box) const override {
            return ptr->bounding_box(time0, time1, output_box);
        }

    public:
        shared_ptr<IHitable> ptr;
};
