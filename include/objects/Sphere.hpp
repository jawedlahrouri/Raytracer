/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Sphere (mathematical object)
*/

#ifndef RAYTRACER_SPHERE_HPP_
#define RAYTRACER_SPHERE_HPP_

#include "math/Point3D.hpp"
#include <cmath>
#include "./utils/Ray.hpp"
#include "./utils/HitRecord.hpp"

namespace RayTracer {
    class Sphere {
    public:
        Math::Point3D center;
        double radius;
        Math::Vector3D color;

        // Constructor
        Sphere(const Math::Point3D& c, double r, const Math::Vector3D& col = Math::Vector3D(255, 0, 0)) : center(c), radius(r), color(col) {}

        bool hits(const Ray& ray, double t_min, double t_max, HitRecord& rec) const;
    };
}

#endif /* !RAYTRACER_SPHERE_HPP_ */
