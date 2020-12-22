#pragma once

#include "Render.h"
#include <cmath>
#include <iostream>

using std::fabs;
using std::sqrt;

/**
 * Vector three double component
 */
class Vector3d
{
  public:
    /**
     * Construct a new Vector 3d object
     */
    Vector3d() : e{0, 0, 0}
    {
    }

    /**
     * Construct a new Vector 3d object
     *
     * @param e0
     * @param e1
     * @param e2
     */
    Vector3d(double e0, double e1, double e2) : e{e0, e1, e2}
    {
    }

    /**
     * return x
     *
     * @return double
     */
    double x() const
    {
        return e[0];
    }

    /**
     * return y
     *
     * @return double
     */
    double y() const
    {
        return e[1];
    }

    /**
     * return z
     *
     * @return double
     */
    double z() const
    {
        return e[2];
    }

    /**
     *
     *
     * @return Vector3d
     */
    Vector3d operator-() const
    {
        return Vector3d(-e[0], -e[1], -e[2]);
    }

    /**
     *
     *
     * @param i
     * @return double
     */
    double operator[](int i) const
    {
        return e[i];
    }

    /**
     *
     *
     * @param i
     * @return double&
     */
    double &operator[](int i)
    {
        return e[i];
    }

    /**
     *
     *
     * @param v
     * @return Vector3d&
     */
    Vector3d &operator+=(const Vector3d &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    /**
     *
     *
     * @param t
     * @return Vector3d&
     */
    Vector3d &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    /**
     *
     *
     * @param t
     * @return Vector3d&
     */
    Vector3d &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    /**
     *
     *
     * @return double
     */
    double length() const
    {
        return sqrt(length_squared());
    }

    /**
     *
     *
     * @return double
     */
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    /**
     *
     *
     * @return true
     * @return false
     */
    bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    /**
     *
     *
     * @return Vector3d
     */
    inline static Vector3d random()
    {
        return Vector3d(random_double(), random_double(), random_double());
    }

    /**
     *
     *
     * @param min
     * @param max
     * @return Vector3d
     */
    inline static Vector3d random(double min, double max)
    {
        return Vector3d(random_double(min, max), random_double(min, max), random_double(min, max));
    }

  public:
    double e[3]; //<
};

// Type aliases for vec3
using point3 = Vector3d; // 3D point
using color = Vector3d;  // RGB color

// vec3 Utility Functions

inline std::ostream &operator<<(std::ostream &out, const Vector3d &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3d operator+(const Vector3d &u, const Vector3d &v)
{
    return Vector3d(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3d operator-(const Vector3d &u, const Vector3d &v)
{
    return Vector3d(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3d operator*(const Vector3d &u, const Vector3d &v)
{
    return Vector3d(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3d operator*(double t, const Vector3d &v)
{
    return Vector3d(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3d operator*(const Vector3d &v, double t)
{
    return t * v;
}

inline Vector3d operator/(Vector3d v, double t)
{
    return (1 / t) * v;
}

inline double dot(const Vector3d &u, const Vector3d &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vector3d cross(const Vector3d &u, const Vector3d &v)
{
    return Vector3d(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector3d unit_vector(Vector3d v)
{
    return v / v.length();
}

inline Vector3d random_in_unit_disk()
{
    while (true)
    {
        auto p = Vector3d(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

inline Vector3d random_in_unit_sphere()
{
    while (true)
    {
        auto p = Vector3d::random(-1, 1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

inline Vector3d random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline Vector3d random_in_hemisphere(const Vector3d &normal)
{
    Vector3d in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline Vector3d reflect(const Vector3d &v, const Vector3d &n)
{
    return v - 2 * dot(v, n) * n;
}

inline Vector3d refract(const Vector3d &uv, const Vector3d &n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vector3d r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vector3d r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
