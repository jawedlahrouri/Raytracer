/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "objects/Rect.hpp"
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"
#include "./utils/Ray.hpp"
#include "exception.hpp"
#include <iostream>

    bool RayTracer::Rect::hits(const Ray& ray) const {
    try {
        double denominator = ray.direction.dot(normal);
        if (std::abs(denominator) < 1e-6)
            return false;
        Math::Vector3D diff = center - ray.origin;
        double t = diff.dot(normal) / denominator;
        if (t < 0)
            return false;
        Math::Point3D hitPoint = ray.origin + ray.direction * t;
        Math::Vector3D localHitPoint = hitPoint - center;
        if (std::abs(localHitPoint.X) <= 0.5 && std::abs(localHitPoint.Y) <= 0.5) {
            return true;
        }
    } catch (const WarningException& e) {
        std::cerr << "WarningException in Rect::hits: " << e.what() << std::endl;
    } catch (const ErrorException& e) {
        std::cerr << "ErrorException in Rect::hits: " << e.what() << std::endl;
    } catch (const CrashException& e) {
        std::cerr << "CrashException in Rect::hits: " << e.what() << std::endl;
    }
    return false;
}