/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Shadow_Ray
*/

#include "plugins/renderer/Shadow_Ray.hpp"

bool Shadow_Ray::hits(const RayTracer::Ray& ray, double t_min, double t_max, const RayTracer::Sphere& s, const RayTracer::Plane& p) const
{
    HitRecord temp_rec;
    // if we touch the first sphere
    if (s.hits(ray, t_min, t_max, temp_rec)) {
        return true;
    }
    if (p.hits(ray, t_min, t_max, temp_rec)) {
        return true;
    }
    return false;
}
