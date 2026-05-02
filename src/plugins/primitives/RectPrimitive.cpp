/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "primitives/RectPrimitive.hpp"

bool Raytracer::RectPrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const {
    Math::Vector3D normal(0, 0, 1);
    double denominator = ray.direction.dot(normal);

    if (std::abs(denominator) < 1e-6)
        return false;
    
    Math::Vector3D origin_vec(ray.origin.X, ray.origin.Y, ray.origin.Z);
    Math::Vector3D center_vec(center.X, center.Y, center.Z);
    Math::Vector3D diff = center_vec - origin_vec;
    double t = diff.dot(normal) / denominator;

    if (t < tMin || t > tMax)
        return false;

    Math::Point3D hitPoint(
        ray.origin.X + ray.direction.X * t,
        ray.origin.Y + ray.direction.Y * t,
        ray.origin.Z + ray.direction.Z * t
    );

    double dx = std::abs(hitPoint.X - center.X);
    double dy = std::abs(hitPoint.Y - center.Y);

    if (dx <= width / 2.0 && dy <= height / 2.0) {
        rec.t = t;
        rec.point = hitPoint;
        rec.normal = (denominator > 0)
            ? Math::Vector3D(-normal.X, -normal.Y, -normal.Z)
            : normal;
        rec.color = color;
        return true;
    }
    return false;
}

Raytracer::AABB Raytracer::RectPrimitive::bounds() const {
    const float PAD = 1e-3f;
    AABB box;
    box.min = Math::Vector3D(
        center.X - width / 2.0f,
        center.Y - height / 2.0f,
        center.Z - PAD
    );
    box.max = Math::Vector3D(
        center.X + width / 2.0f,
        center.Y + height / 2.0f,
        center.Z + PAD
    );
    return box;
}

Math::Point3D Raytracer::RectPrimitive::centroid() const {
    return center;
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