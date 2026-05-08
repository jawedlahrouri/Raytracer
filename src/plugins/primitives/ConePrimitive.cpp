/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ConePrimitive
*/

#include "primitives/ConePrimitive.hpp"

bool Raytracer::ConePrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
    double k = radius / height;
    double k2 = k * k;
    double y_tip = center.Y + height / 2.0;

    double oc_X = ray.origin.X - center.X;
    double oc_Y = ray.origin.Y - y_tip;
    double oc_Z = ray.origin.Z - center.Z;

    double a = (ray.direction.X * ray.direction.X) + (ray.direction.Z * ray.direction.Z) - k2 * (ray.direction.Y * ray.direction.Y);
    double b = 2.0 * (oc_X * ray.direction.X + oc_Z * ray.direction.Z - k2 * oc_Y * ray.direction.Y);
    double c = (oc_X * oc_X) + (oc_Z * oc_Z) - k2 * (oc_Y * oc_Y);

    double delta = (b * b) - (4 * a * c);

    if (delta >= 0 && a != 0) {
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

        double dy = hitPoint.Y - center.Y;

        // Ensure hit point is within the vertical bounds of the cone
        if (dy < -height / 2.0 || dy > height / 2.0) {
            // Check the other root if the first one was out of vertical bounds
            if (t == t1) {
                t = t2;
                if (t >= tMin && t <= tMax) {
                    hitPoint = Math::Point3D(
                        ray.origin.X + ray.direction.X * t,
                        ray.origin.Y + ray.direction.Y * t,
                        ray.origin.Z + ray.direction.Z * t
                    );
                    dy = hitPoint.Y - center.Y;
                    if (dy < -height / 2.0 || dy > height / 2.0) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        rec.t = t;
        rec.point = hitPoint;

        // Calculate normal
        double hit_y_diff = hitPoint.Y - y_tip;
        Math::Vector3D outward_normal(
            hitPoint.X - center.X,
            -k2 * hit_y_diff,
            hitPoint.Z - center.Z
        );

        // Normalize the normal vector
        double norm_length = std::sqrt(outward_normal.X * outward_normal.X + outward_normal.Y * outward_normal.Y + outward_normal.Z * outward_normal.Z);
        if (norm_length > 0) {
            outward_normal.X /= norm_length;
            outward_normal.Y /= norm_length;
            outward_normal.Z /= norm_length;
        }

        rec.normal = outward_normal;
        rec.color = color;
        rec.material = material.get();
        
        return true;
    }
    return false;
}

Raytracer::AABB Raytracer::ConePrimitive::bounds() const
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

Math::Point3D Raytracer::ConePrimitive::centroid() const
{
    return center;
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) {
        return new Raytracer::ConePrimitive(data);
    }
}
