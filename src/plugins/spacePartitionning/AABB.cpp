/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AABB for BVH algo to process i a better way the shapes
*/

#include "./spacePartitionning/AABB.hpp"

bool Raytracer::AABB::intersect(const Ray& ray, double tMin, double tMax) const
{
    const double dirs[3] = { ray.direction.X, ray.direction.Y, ray.direction.Z };
    const double origins[3] = { ray.origin.X, ray.origin.Y,    ray.origin.Z    };
    const double mins[3] = { min.X, min.Y, min.Z};
    const double maxs[3] = { max.X, max.Y, max.Z};

    for (int i = 0; i < 3; ++i) {
        double d  = dirs[i];
        double o  = origins[i];
        double mn = mins[i];
        double mx = maxs[i];

        if (std::abs(d) < 1e-8) {
            if (o < mn || o > mx)
                return false;
        } else {
            double t0 = (mn - o) / d;
            double t1 = (mx - o) / d;
            if (t0 > t1) std::swap(t0, t1);
            tMin = std::max(tMin, t0);
            tMax = std::min(tMax, t1);
            if (tMax <= tMin)
                return false;
        }
    }
    return true;
}


float Raytracer::AABB::surfaceArea() const
{
    Math::Vector3D d = max - min;
    return 2.f * (d.X*d.Y + d.Y*d.Z + d.Z*d.X);
}
