/**
 * @file 7DemoDiffuse.cpp
 *
 * @date 2020-12-18
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Camera.h"
#include "Color.h"
#include "Hit.h"
#include "Render.h"
#include "Sphere.h"

// vec2 random_in_hemisphere(const vec3 &normal)
// {
//     vec3 in_unit_sphere = random_in_unit_sphere();
//     if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
//         return in_unit_sphere;
//     else
//         return -in_unit_sphere;
// }

color ray_color(const Ray &r, const IHitable &world, int depth)
{
    HitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec))
    {
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth - 1);
    }

    Vector3d unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    // World

    HittableList world;
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Camera
    // camera cam;
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vector3d vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Carmera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}