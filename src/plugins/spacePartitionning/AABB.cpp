/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AABB for BVH algo to process i a better way the shapes
*/

#include "./spacePartitionning/AABB.hpp"

bool Raytracer::AABB::intersect(const Ray& ray, double tMin, double tMax) const
{
    for (int i = 0; i < 3; ++i) {
            float d = (&ray.direction.X)[i];
            float o = (&ray.origin.X)[i];
            float mn = (&min.X)[i];
            float mx = (&max.X)[i];

            if (std::abs(d) < 1e-8f) { // sert a verifier si le rayons n'est pas egale ou tres proche de 0
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
