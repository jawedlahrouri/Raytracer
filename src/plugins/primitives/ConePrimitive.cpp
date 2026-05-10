/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ConePrimitive
*/

#include "primitives/ConePrimitive.hpp"
#include <algorithm>

bool Raytracer::ConePrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
    Math::Vector3D o = (ray.origin - center).rotateZ(-_rotation.Z).rotateY(-_rotation.Y).rotateX(-_rotation.X);
    Math::Vector3D d = ray.direction.rotateZ(-_rotation.Z).rotateY(-_rotation.Y).rotateX(-_rotation.X);
    double k = radius / height;
    double k2 = k * k;
    double y_tip = height / 2.0;
    double oc_X = o.X;
    double oc_Y = o.Y - y_tip;
    double oc_Z = o.Z;
    double a = (d.X * d.X) + (d.Z * d.Z) - k2 * (d.Y * d.Y);
    double b = 2.0 * (oc_X * d.X + oc_Z * d.Z - k2 * oc_Y * d.Y);
    double c = (oc_X * oc_X) + (oc_Z * oc_Z) - k2 * (oc_Y * oc_Y);
    double delta = (b * b) - (4 * a * c);

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
        double dy = hit_local.Y;

        if (dy < -height / 2.0 || dy > height / 2.0) {
            if (t == t1) {
                t = t2;
                if (t >= tMin && t <= tMax) {
                    hit_local = o + (d * t);
                    dy = hit_local.Y;
                    if (dy < -height / 2.0 || dy > height / 2.0)
                        return false;
                } else
                    return false;
            } else
                return false;
        }

        rec.t = t;
        rec.ray = ray;
        rec.point = ray.at(t);

        double hit_y_diff = hit_local.Y - y_tip;
        Math::Vector3D local_normal(hit_local.X, -k2 * hit_y_diff, hit_local.Z);
        rec.normal = local_normal.normalize().rotateX(_rotation.X).rotateY(_rotation.Y).rotateZ(_rotation.Z);
        rec.color = color;
        rec.material = material.get();
        return true;
    }
    return false;
}

Raytracer::AABB Raytracer::ConePrimitive::bounds() const
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

Math::Point3D Raytracer::ConePrimitive::centroid() const {
    return center;
}

extern "C" {
    int getType()
    {
        return 0;
    }
    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) { return new Raytracer::ConePrimitive(data); }
}
