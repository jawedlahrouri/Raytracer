/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "primitives/CylinderPrimitive.hpp"

bool Raytracer::CylinderPrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
    double oc_X = ray.origin.X - center.X;
    double oc_Z = ray.origin.Z - center.Z;
    double a = (ray.direction.X * ray.direction.X) + (ray.direction.Z * ray.direction.Z);
    double b = 2.0 * ((oc_X * ray.direction.X) + (oc_Z * ray.direction.Z));
    double c = (oc_X * oc_X) + (oc_Z * oc_Z) - (radius * radius);
    double delta = (b * b) - (4 * (a * c));

    if (delta >= 0) {
        double sqrt_delta = std::sqrt(delta);
        double t1 = (-b - sqrt_delta) / (2.0 * a);
        double t2 = (-b + sqrt_delta) / (2.0 * a);
        double t = t1;

        if (t < tMin || t > tMax) {
            t = t2;
            if (t < tMin || t > tMax) {
                return false;
            }
        }

        Math::Point3D hitPoint(
            ray.origin.X + ray.direction.X * t,
            ray.origin.Y + ray.direction.Y * t,
            ray.origin.Z + ray.direction.Z * t
        );

        double dy = std::abs(hitPoint.Y - center.Y);

        if (dy > height / 2.0)
            return false;

        rec.t = t;
        rec.point = hitPoint;

        Math::Vector3D outward_normal(
            (hitPoint.X - center.X) / radius,
            0.0,
            (hitPoint.Z - center.Z) / radius
        );

        rec.normal = outward_normal;
        rec.color = color;
        
        return true;
    }
    return false;
}

Raytracer::AABB Raytracer::CylinderPrimitive::bounds() const
{
    AABB box;
    box.min = Math::Vector3D(
        center.X - radius,
        center.Y - height / 2.0f,
        center.Z - radius
    );
    box.max = Math::Vector3D(
        center.X + radius,
        center.Y + height / 2.0f,
        center.Z + radius
    );
    return box;
}

Math::Point3D Raytracer::CylinderPrimitive::centroid() const
{
    return center;
}

extern "C" {
    int getType()
    {
        return 0;
    }

    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) {
        return new Raytracer::CylinderPrimitive(data);
    }
}