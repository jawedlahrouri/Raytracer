/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Shadow_Ray
*/

#include "plugins/renderer/Shadow_Ray.hpp"


bool Raytracer::Shadow_Ray::hits(const Raytracer::Ray& ray, double t_min, double t_max, const Raytracer::Sphere& s, const Raytracer::PlaneClass& p) const
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
