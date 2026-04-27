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

namespace Raytracer {
    class Sphere {
    public:
        Math::Point3D center;
        double radius;

        // Constructor
        Sphere(const Math::Point3D& c, double r) : center(c), radius(r) {}

        bool hits(const Ray& ray) const;
    };
}

#endif /* !RAYTRACER_SPHERE_HPP_ */
