/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Sphere
*/


#include "objects/Sphere.hpp"
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"
#include "./utils/Ray.hpp"
#include "exception.hpp"
#include <iostream>

namespace RayTracer {
    // Formula:
    // (D·D)t^2 + 2D·(O-C)t + (O-C)·(O-C) - R^2 = 0
    bool Sphere::hits(const Ray& ray) const {
        try {
            Math::Vector3D oc = ray.origin - Math::Vector3D(center.X, center.Y, center.Z);
            double a = ray.direction.dot(ray.direction);
            double b = 2.0 * oc.dot(ray.direction);
            double c = oc.dot(oc) - radius * radius;
            double discriminant = b * b - 4 * a * c;
            return discriminant >= 0;
        } catch (const WarningException& e) {
            std::cerr << "WarningException in Sphere::hits: " << e.what() << std::endl;
            return false;
        } catch (const ErrorException& e) {
            std::cerr << "ErrorException in Sphere::hits: " << e.what() << std::endl;
            return false;
        } catch (const CrashException& e) {
            std::cerr << "CrashException in Sphere::hits: " << e.what() << std::endl;
            return false;
        } catch (const Exception& e) {
            std::cerr << "Exception in Sphere::hits: " << e.what() << std::endl;
            return false;
        } catch (...) {
            std::cerr << "Unknown exception in Sphere::hits" << std::endl;
            return false;
        }
    }

}
