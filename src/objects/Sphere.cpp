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
#include "./utils/HitRecord.hpp"
#include "exception.hpp"
#include <iostream>

static void fill_hit_record(HitRecord& rec, double t, const Math::Point3D& hitPoint, const Math::Point3D& center, double radius, const Math::Vector3D& color) {
    rec.t = t;
    rec.point = Math::Vector3D(hitPoint.X, hitPoint.Y, hitPoint.Z);
    rec.normal = (hitPoint - center) / radius;
    rec.color = color;
}

namespace RayTracer {
    bool Sphere::hits(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
        try {
            Math::Vector3D oc = ray.origin - center;
            double a = ray.direction.dot(ray.direction);
            double b = 2.0 * oc.dot(ray.direction);
            double c = oc.dot(oc) - radius * radius;
            double discriminant = b * b - 4 * a * c;
            
            // if is 0 no intersection, if is 
            if (discriminant < 0)
                return false;
            double sqrtd = std::sqrt(discriminant);
            
            // find the nearest root that lies in the acceptable range
            double root = (-b - sqrtd) / (2.0 * a);
            if (root <= t_min || t_max <= root) {
                root = (-b + sqrtd) / (2.0 * a);
                if (root <= t_min || t_max <= root)
                    return false;
            }
            Math::Point3D temp_point = ray.origin + ray.direction * root;
            fill_hit_record(rec, root, temp_point, center, radius, color);
            return true;
        } catch (const Exception& e) {
            return false;
        }
    }
}
