/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** planes
*/

#include "primitives/PlanePrimitive.hpp"

/// Fills the hit record with the intersection data
static void fill_hit_record(HitRecord& rec, double t, const Math::Point3D& hitPoint, const Math::Vector3D& normal, double denom, const Math::Vector3D& color) {
    rec.t = t;
    rec.point = hitPoint;
    rec.normal = normal;
    if (denom > 0)
        rec.normal = Math::Vector3D(-normal.X, -normal.Y, -normal.Z);
    rec.color = color;
}

bool Raytracer::PlanePrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const {
    // t = [(center - ray.origin) . normal] / [ray.direction . normal]
    double denom = ray.direction.dot(normal);
    if (std::abs(denom) < 1e-6)
        return false;

    // Calculate the intersection point
    Math::Vector3D diff(center.X - ray.origin.X, center.Y - ray.origin.Y, center.Z - ray.origin.Z);
    double t = diff.dot(normal) / denom;

    if (t < tMin || t > tMax)
        return false;

    // Fill the hit record
    Math::Point3D hitPoint(
        ray.origin.X + ray.direction.X * t,
        ray.origin.Y + ray.direction.Y * t,
        ray.origin.Z + ray.direction.Z * t
    );
    fill_hit_record(rec, t, hitPoint, normal, denom, color);
    return true;
}

Raytracer::AABB Raytracer::PlanePrimitive::bounds() const {
    // Planes are infinite — return a large AABB padded around the center
    const float BIG = 1e6f;
    const float THIN = 1e-3f;
    Math::Vector3D absN(std::abs(normal.X), std::abs(normal.Y), std::abs(normal.Z));

    AABB box;
    box.min = Math::Vector3D(
        (absN.X > 0.9f) ? center.X - THIN : center.X - BIG,
        (absN.Y > 0.9f) ? center.Y - THIN : center.Y - BIG,
        (absN.Z > 0.9f) ? center.Z - THIN : center.Z - BIG
    );
    box.max = Math::Vector3D(
        (absN.X > 0.9f) ? center.X + THIN : center.X + BIG,
        (absN.Y > 0.9f) ? center.Y + THIN : center.Y + BIG,
        (absN.Z > 0.9f) ? center.Z + THIN : center.Z + BIG
    );
    return box;
}

Math::Point3D Raytracer::PlanePrimitive::centroid() const {
    return center;
}

void Raytracer::PlanePrimitive::setName(const std::string& name)
{
    _name = name;
}

void Raytracer::PlanePrimitive::setPosition(const Math::Point3D& position)
{
    center = position;
}

void Raytracer::PlanePrimitive::setAxis(const Math::Vector3D& axis)
{
    normal = axis;
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