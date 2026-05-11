/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "primitives/CylinderPrimitive.hpp"
#include <algorithm>

bool Raytracer::CylinderPrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
    Math::Vector3D o = (ray.origin - center).rotateZ(-_rotation.Z).rotateY(-_rotation.Y).rotateX(-_rotation.X);
    Math::Vector3D d = ray.direction.rotateZ(-_rotation.Z).rotateY(-_rotation.Y).rotateX(-_rotation.X);
    double a = (d.X * d.X) + (d.Z * d.Z);
    double b = 2.0 * ((o.X * d.X) + (o.Z * d.Z));
    double c = (o.X * o.X) + (o.Z * o.Z) - (radius * radius);
    double delta = (b * b) - (4 * (a * c));

    if (delta >= 0 && a != 0) {
        double sqrt_delta = std::sqrt(delta);
        double t1 = (-b - sqrt_delta) / (2.0 * a);
        double t2 = (-b + sqrt_delta) / (2.0 * a);
        double t = t1;

        if (t < tMin || t > tMax) {
            t = t2;
            if (t < tMin || t > tMax)
                return false;
        }

        Math::Vector3D hit_local = o + (d * t);

        if (std::abs(hit_local.Y) > height / 2.0) {
            if (t == t1) {
                t = t2;
                if (t >= tMin && t <= tMax) {
                    hit_local = o + (d * t);
                    if (std::abs(hit_local.Y) > height / 2.0)
                    return false;
                } else
                    return false;
            } else
                return false;
        }

        rec.t = t;
        rec.ray = ray;
        rec.point = ray.at(t);

        Math::Vector3D local_normal(hit_local.X / radius, 0.0, hit_local.Z / radius);
        rec.normal = local_normal.rotateX(_rotation.X).rotateY(_rotation.Y).rotateZ(_rotation.Z);
        rec.color = color;
        rec.material = material.get();
        return true;
    }
    return false;
}

Raytracer::AABB Raytracer::CylinderPrimitive::bounds() const
{
    AABB box;
    box.min = Math::Vector3D(1e9, 1e9, 1e9);
    box.max = Math::Vector3D(-1e9, -1e9, -1e9);

    Math::Vector3D corners[8] = {
        Math::Vector3D(-radius, -height/2, -radius), Math::Vector3D(radius, -height/2, -radius),
        Math::Vector3D(-radius, height/2, -radius), Math::Vector3D(radius, height/2, -radius),
        Math::Vector3D(-radius, -height/2, radius), Math::Vector3D(radius, -height/2, radius),
        Math::Vector3D(-radius, height/2, radius), Math::Vector3D(radius, height/2, radius)
    };

    for (int i = 0; i < 8; i++) {
        Math::Vector3D rotated = corners[i].rotateX(_rotation.X).rotateY(_rotation.Y).rotateZ(_rotation.Z);
        Math::Vector3D world_corner(center.X + rotated.X, center.Y + rotated.Y, center.Z + rotated.Z);
        
        box.min.X = std::min(box.min.X, world_corner.X); box.min.Y = std::min(box.min.Y, world_corner.Y); box.min.Z = std::min(box.min.Z, world_corner.Z);
        box.max.X = std::max(box.max.X, world_corner.X); box.max.Y = std::max(box.max.Y, world_corner.Y); box.max.Z = std::max(box.max.Z, world_corner.Z);
    }
    return box;
}

Math::Point3D Raytracer::CylinderPrimitive::centroid() const { return center; }

extern "C" {
    int getType() { return 0; }
    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) { return new Raytracer::CylinderPrimitive(data); }
}
