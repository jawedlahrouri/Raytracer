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
        // t = [(center - ray.origin) . normal] / [ray.direction . normal]
        double denom = ray.direction.dot(normal);
        if (std::abs(denom) < 1e-6)
            return false;
        Math::Vector3D diff = center - ray.origin; // Point3D - Point3D = Vector3D
        double t = diff.dot(normal) / denom;
        return t > 0;
    } catch (const WarningException& e) {
        std::cerr << "WarningException in Plane::hits: " << e.what() << std::endl;
        return false;
    }
}