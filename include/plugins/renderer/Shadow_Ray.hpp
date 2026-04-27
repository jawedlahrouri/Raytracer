/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Shadow_Ray
*/

#ifndef SHADOW_RAY_HPP_
#define SHADOW_RAY_HPP_

#include "utils/HitRecord.hpp"
#include "utils/Ray.hpp"
#include "objects/Sphere.hpp"
#include "objects/Plane.hpp"

class Shadow_Ray {
    public:
        Shadow_Ray() = default;
        ~Shadow_Ray() = default;

        // check if the ray hits
        bool hits(const RayTracer::Ray& ray, double t_min, double t_max, const RayTracer::Sphere& s, const RayTracer::Plane& p) const;
};

#endif /* !SHADOW_RAY_HPP_ */
