/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** planes
*/

#include "primitives/PlanePrimitive.hpp"

/// Fills the hit record with the intersection 
static void fill_hit_record(HitRecord& rec, double t, const Math::Point3D& hitPoint, const Math::Vector3D& normal, double denom, const Math::Vector3D& color) {
    rec.t = t;
    rec.point = Math::Vector3D(hitPoint.X, hitPoint.Y, hitPoint.Z);
    rec.normal = normal;
    if (denom > 0)
        rec.normal = Math::Vector3D(-normal.X, -normal.Y, -normal.Z);
    rec.color = color;
}

bool Raytracer::PlanePrimitive::intersect(const Ray& ray, HitRecord& rec) const {
    try {
        double t_min = 0.001;
        double t_max = 1000000.0;
        // t = [(center - ray.origin) . normal] / [ray.direction . normal]
        double denom = ray.direction.dot(normal);
        if (std::abs(denom) < 1e-6)
            return false;
            
        // Calculate the intersection point
        Math::Vector3D diff = center - ray.origin;
        double t = diff.dot(normal) / denom;
        
        // Check the intersection point
        if (t < t_min || t > t_max)
            return false;
            
        // Fill the hit record
        Math::Point3D temp_point = ray.origin + ray.direction * t;
        fill_hit_record(rec, t, temp_point, normal, denom, color);
        
        return true;
    } catch (const Exception& e) {
        return false;
    }
}

void Raytracer::PlanePrimitive::drawShape()
{
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    Raytracer::IPrimitive* entryPoint(const Raytracer::Plane& data) {
        return new Raytracer::PlanePrimitive(data);
    }
}