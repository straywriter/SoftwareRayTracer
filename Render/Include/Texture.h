/**
 * @file Texture.h
 *
 * @date 2020-12-18
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "Image.h"
#include "Perlin.h"
#include "Render.h"

#include <iostream>

/**
 * texture
 */
class Texture
{
  public:
    virtual color value(double u, double v, const Vector3d &p) const = 0;
};

/**
 * solid color
 */
class SolidColor : public Texture
{
  public:
    SolidColor()
    {
    }
    SolidColor(color c) : color_value(c)
    {
    }

    SolidColor(double red, double green, double blue) : SolidColor(color(red, green, blue))
    {
    }

    virtual color value(double u, double v, const Vector3d &p) const override
    {
        return color_value;
    }

  private:
    color color_value;
};

/**
 * 
 */
class CheckerTexture : public Texture
{
  public:
    CheckerTexture()
    {
    }

    CheckerTexture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd) : even(_even), odd(_odd)
    {
    }

    CheckerTexture(color c1, color c2) : even(make_shared<SolidColor>(c1)), odd(make_shared<SolidColor>(c2))
    {
    }

    virtual color value(double u, double v, const Vector3d &p) const override
    {
        auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sines < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }

  public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;
};

class NoiseTexture : public Texture
{
  public:
    NoiseTexture()
    {
    }
    NoiseTexture(double sc) : scale(sc)
    {
    }

    virtual color value(double u, double v, const Vector3d &p) const override
    {
        // return color(1,1,1)*0.5*(1 + noise.turb(scale * p));
        // return color(1,1,1)*noise.turb(scale * p);
        return color(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
    }

  public:
    Perlin noise;
    double scale;
};

class ImageTexture : public Texture
{
  public:
    const static int bytes_per_pixel = 3;

    ImageTexture() : data(nullptr), width(0), height(0), bytes_per_scanline(0)
    {
    }

    ImageTexture(const char *filename)
    {
        auto components_per_pixel = bytes_per_pixel;

        data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

        if (!data)
        {
            std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
            width = height = 0;
        }

        bytes_per_scanline = bytes_per_pixel * width;
    }

    ~ImageTexture()
    {
        STBI_FREE(data);
    }

    virtual color value(double u, double v, const Vector3d &p) const override
    {
        // If we have no texture data, then return solid cyan as a debugging aid.
        if (data == nullptr)
            return color(0, 1, 1);

        // Clamp input texture coordinates to [0,1] x [1,0]
        u = clamp(u, 0.0, 1.0);
        v = 1.0 - clamp(v, 0.0, 1.0); // Flip V to image coordinates

        auto i = static_cast<int>(u * width);
        auto j = static_cast<int>(v * height);

        // Clamp integer mapping, since actual coordinates should be less than 1.0
        if (i >= width)
            i = width - 1;
        if (j >= height)
            j = height - 1;

        const auto color_scale = 1.0 / 255.0;
        auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

        return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
    }

  private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;
};
