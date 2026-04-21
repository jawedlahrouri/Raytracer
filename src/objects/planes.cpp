/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** planes
*/

#include "math/Point3D.hpp"
#include "objects/Plane.hpp"
#include "exception.hpp"
#include <iostream>

bool RayTracer::Plane::hits(const Ray& ray) const {
    try {
            // t = [(P0 - O) . n] / [D . n]
            Math::Vector3D P0(center.X, center.Y, center.Z);
            Math::Vector3D n = normal;
            Math::Vector3D O = ray.origin;
            Math::Vector3D D = ray.direction;
            double denom = D.dot(n);
            if (std::abs(denom) < 1e-6) // protection for the division by zero
                return false;
            double t = (P0 - O).dot(n) / denom;
            return t > 0;
    } catch (const WarningException& e) {
        std::cerr << "WarningException in Plane::hits: " << e.what() << std::endl;
        return false;
    }
}