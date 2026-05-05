/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ppm_export
*/

#include "plugins/renderer/ppm_export.hpp"
#include "RaytracerType.hpp"
#include "exception.hpp"
#include <iostream>

void Raytracer::PPMExporter::write_color(unsigned int r, unsigned int g, unsigned int b)
{
    unsigned int color[3];
    color[Raytracer::RED] = r;
    color[Raytracer::GREEN] = g;
    color[Raytracer::BLUE] = b;


    if (color[Raytracer::RED] > 255 || color[Raytracer::GREEN] > 255 || color[Raytracer::BLUE] > 255) {
        throw ErrorException("Color values must be in the range [0, 255]");
    }

    Math::Vector3D colorVec(color[Raytracer::RED], color[Raytracer::GREEN], color[Raytracer::BLUE]);
}

void Raytracer::PPMExporter::write_header(int width, int height)
{
    std::cout << "P3\n" << width << " " << height << "\n255\n";
}

void Raytracer::PPMExporter::write_pixel(int r, int g, int b)
{
    write_color(r, g, b);
    std::cout << r << " " << g << " " << b << "\n";
}

// void Raytracer::PPMExporter::write_image(int width, int height, const std::vector<std::vector<Math::Vector3D>>& pixels)
// {
//     write_header(width, height);
//     for (int j = 0; j < height; ++j) {
//         for (int i = 0; i < width; ++i) {
//             const Math::Vector3D& color = pixels[j][i];
//             write_pixel(static_cast<int>(color.X), static_cast<int>(color.Y), static_cast<int>(color.Z));
//         }
//     }
// }

void Raytracer::PPMExporter::write_image(int width, int height,
    const std::vector<std::vector<Math::Vector3D>>& pixels)
{
    write_header(width, height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            const Math::Vector3D& color = pixels[j][i];
            write_pixel(
                static_cast<int>(color.X * 255.99),
                static_cast<int>(color.Y * 255.99),
                static_cast<int>(color.Z * 255.99)
            );
        }
    }
}