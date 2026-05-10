/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "primitives/RectPrimitive.hpp"
#include <algorithm>

bool Raytracer::RectPrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const {
    Math::Vector3D o = (ray.origin - center).rotateZ(-_rotation.Z).rotateY(-_rotation.Y).rotateX(-_rotation.X);
    Math::Vector3D d = ray.direction.rotateZ(-_rotation.Z).rotateY(-_rotation.Y).rotateX(-_rotation.X);

    Math::Vector3D normal(0, 0, 1);
    double denominator = d.dot(normal);

    if (std::abs(denominator) < 1e-6)
        return false;

    Math::Vector3D diff(0 - o.X, 0 - o.Y, 0 - o.Z);
    double t = diff.dot(normal) / denominator;

    if (t < tMin || t > tMax)
        return false;

    Math::Vector3D hit_local = o + (d * t);
    double dx = std::abs(hit_local.X);
    double dy = std::abs(hit_local.Y);

    if (dx <= width / 2.0 && dy <= height / 2.0) {
        rec.t = t;
        rec.ray = ray;
        rec.point = ray.at(t);
        
        Math::Vector3D world_normal = normal.rotateX(_rotation.X).rotateY(_rotation.Y).rotateZ(_rotation.Z);
        rec.normal = (denominator > 0) ? Math::Vector3D(-world_normal.X, -world_normal.Y, -world_normal.Z) : world_normal;
        rec.color = color;
        rec.material = material.get();
        return true;
    }
    return false;
}

Raytracer::AABB Raytracer::RectPrimitive::bounds() const {
    AABB box;
    box.min = Math::Vector3D(1e9, 1e9, 1e9);
    box.max = Math::Vector3D(-1e9, -1e9, -1e9);
    Math::Vector3D corners[4] = {
        Math::Vector3D(-width/2, -height/2, 0), Math::Vector3D(width/2, -height/2, 0),
        Math::Vector3D(-width/2, height/2, 0), Math::Vector3D(width/2, height/2, 0)
    };

    for (int i = 0; i < 4; i++) {
        Math::Vector3D rotated = corners[i].rotateX(_rotation.X).rotateY(_rotation.Y).rotateZ(_rotation.Z);
        Math::Vector3D world_corner(center.X + rotated.X, center.Y + rotated.Y, center.Z + rotated.Z);
        
        box.min.X = std::min(box.min.X, world_corner.X); box.min.Y = std::min(box.min.Y, world_corner.Y); box.min.Z = std::min(box.min.Z, world_corner.Z);
        box.max.X = std::max(box.max.X, world_corner.X); box.max.Y = std::max(box.max.Y, world_corner.Y); box.max.Z = std::max(box.max.Z, world_corner.Z);
    }
    box.min = box.min - Math::Vector3D(0.001, 0.001, 0.001);
    box.max = box.max + Math::Vector3D(0.001, 0.001, 0.001);
    return box;
}

Math::Point3D Raytracer::RectPrimitive::centroid() const {
    return center;
}

extern "C" {
    int getType()
    {
        return 0;
    }

    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) {
        return new Raytracer::RectPrimitive(data);
    }
}
