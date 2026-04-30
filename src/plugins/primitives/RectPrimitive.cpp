/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "primitives/RectPrimitive.hpp"

static void fill_hit_record(HitRecord& rec, double t, const Math::Point3D& hitPoint, const Math::Vector3D& normal, double denominator, const Math::Vector3D& color) {
    rec.t = t;
    rec.point = Math::Vector3D(hitPoint.X, hitPoint.Y, hitPoint.Z);
    rec.normal = normal;
    if (denominator > 0)
        rec.normal = Math::Vector3D(-normal.X, -normal.Y, -normal.Z);
    rec.color = color;
}

bool Raytracer::RectPrimitive::intersect(const Ray& ray, HitRecord& rec) const {
    double t_min = 0.001;
    double t_max = 1000000.0;
    Math::Vector3D normal(0, 0, 1);
    double denominator = ray.direction.dot(normal);
    
    if (std::abs(denominator) < 1e-6)
        return false;
        
    Math::Vector3D origin_vec(ray.origin.X, ray.origin.Y, ray.origin.Z);
    Math::Vector3D center_vec(center.X, center.Y, center.Z);
    Math::Vector3D diff = center_vec - origin_vec;
    double t = diff.dot(normal) / denominator;
    
    if (t < t_min || t > t_max)
        return false;

    Math::Point3D hitPoint = Math::Point3D(ray.origin.X + ray.direction.X * t, 
    ray.origin.Y + ray.direction.Y * t, 
    ray.origin.Z + ray.direction.Z * t);
    
    double dx = std::abs(hitPoint.X - center.X);
    double dy = std::abs(hitPoint.Y - center.Y);

    if (dx <= width / 2.0 && dy <= height / 2.0) {
        fill_hit_record(rec, t, hitPoint, normal, denominator, color);
        return true;
    }
    return false;
}

void Raytracer::RectPrimitive::drawShape()
{
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) {
        return new Raytracer::RectPrimitive(data);
    }
}