#pragma once
#include "Vector3d.h"

class Ray
{
     public:
    point3 orig;
    Vector3d dir;
    double tm;
  public:
    Ray()
    {
    }
    Ray(const point3 &origin, const Vector3d &direction) : orig(origin), dir(direction), tm(0)
    {
    }

    Ray(const point3 &origin, const Vector3d &direction, double time) : orig(origin), dir(direction), tm(time)
    {
    }

    point3 origin() const
    {
        return orig;
    }
    Vector3d direction() const
    {
        return dir;
    }
    double time() const
    {
        return tm;
    }

    point3 at(double t) const
    {
        return orig + t * dir;
    }

 
};
