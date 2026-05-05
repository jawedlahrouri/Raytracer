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
#include <fstream>
#include <sstream>

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

void Raytracer::PPMExporter::write_header(std::ostream& os, int width, int height)
{
    os << "P3\n" << width << " " << height << "\n255\n";
}

void Raytracer::PPMExporter::write_pixel(std::ostream& os, int r, int g, int b)
{
    write_color(r, g, b);
    os << r << " " << g << " " << b << "\n";
}

void Raytracer::PPMExporter::write_image(int width, int height,
    const std::vector<std::vector<Math::Vector3D>>& pixels, const std::string& filename)
{
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw ErrorException("Could not open file to write PPM image");
    }
    std::stringstream buffer;
    write_header(buffer, width, height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            const Math::Vector3D& color = pixels[j][i];
            write_pixel(buffer,
                static_cast<int>(color.X * 255.99),
                static_cast<int>(color.Y * 255.99),
                static_cast<int>(color.Z * 255.99)
            );
        }
    }
    file << buffer.str();
    file.close();
}