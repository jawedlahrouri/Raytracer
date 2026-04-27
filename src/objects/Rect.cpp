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
#include "./utils/HitRecord.hpp"
#include "exception.hpp"
#include <iostream>

/// Fills the hit record with the intersectio
static void fill_hit_record(HitRecord& rec, double t, const Math::Point3D& hitPoint, const Math::Vector3D& normal, double denominator, const Math::Vector3D& color) {
    rec.t = t;
    rec.point = Math::Vector3D(hitPoint.X, hitPoint.Y, hitPoint.Z);
    rec.normal = normal;
    if (denominator > 0)
        rec.normal = Math::Vector3D(-normal.X, -normal.Y, -normal.Z);
    rec.color = color;
}

bool Raytracer::Rect::hits(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    try {
        double denominator = ray.direction.dot(normal);
        if (std::abs(denominator) < 1e-6)
            return false;
            
        Math::Vector3D diff = center - ray.origin;
        double t = diff.dot(normal) / denominator;
        
        // Check the intersection point
        if (t < t_min || t > t_max)
            return false;
        Math::Point3D hitPoint = ray.origin + ray.direction * t;
        Math::Vector3D localHitPoint = hitPoint - center;
        // Check the hit point 
        if (std::abs(localHitPoint.X) <= 0.5 && std::abs(localHitPoint.Y) <= 0.5) {
            fill_hit_record(rec, t, hitPoint, normal, denominator, color);
            return true;
        }
    } catch (const Exception& e) {
        return false;
    }
    return false;
}