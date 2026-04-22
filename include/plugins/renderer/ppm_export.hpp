/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ppm_export
*/

#ifndef PPM_EXPORT_HPP_
#define PPM_EXPORT_HPP_

#include "RaytracerType.hpp"
#include "math/Vector3D.hpp"
#include <vector>

class PPMExporter {
    public:
        PPMExporter() = default;
        ~PPMExporter() = default;

        void write_color(unsigned int r, unsigned int g, unsigned int b);
        void write_header(int width, int height);
        void write_pixel(int r, int g, int b);
        void write_image(int width, int height, const std::vector<std::vector<Math::Vector3D>>& pixels);
};

#endif /* !PPM_EXPORT_HPP_ */
