#pragma once

#include "Render.h"

class camera
{
  public:
    /**
     * Construct a new camera object
     */
    camera() : camera(point3(0, 0, -1), point3(0, 0, 0), Vector3d(0, 1, 0), 40, 1, 0, 10)
    {
    }

    camera(double vfov, // vertical field-of-view in degrees
           double aspect_ratio)
    {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = Vector3d(viewport_width, 0.0, 0.0);
        vertical = Vector3d(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vector3d(0, 0, focal_length);
    }

    camera(point3 lookfrom, point3 lookat, Vector3d vup,
           double vfov, // vertical field-of-view in degrees
           double aspect_ratio)
    {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto w = unit_vector(lookfrom - lookat);
        auto u = unit_vector(cross(vup, w));
        auto v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    camera(point3 lookfrom, point3 lookat, Vector3d vup,
           double vfov, // vertical field-of-view in degrees
           double aspect_ratio, double aperture, double focus_dist, double _time0 = 0, double _time1 = 0)
    {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
        time0 = _time0;
        time1 = _time1;
    }

    Ray get_ray(double s, double t) const
    {
        Vector3d rd = lens_radius * random_in_unit_disk();
        Vector3d offset = u * rd.x() + v * rd.y();
        return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset,
                   random_double(time0, time1));
    }

  private:
    point3 origin;
    point3 lower_left_corner;
    Vector3d horizontal;
    Vector3d vertical;
    Vector3d u, v, w;
    double lens_radius;
    double time0, time1; // shutter open/close times
};
