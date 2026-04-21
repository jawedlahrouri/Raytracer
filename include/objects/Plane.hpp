/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** planes
*/

#ifndef PLANES_HPP_
#define PLANES_HPP_

#include "math/Point3D.hpp"
#include <cmath>
#include "./utils/Ray.hpp"
#include "math/Vector3D.hpp"

namespace RayTracer {
    class Plane {
    public:
        Math::Point3D center;
        Math::Vector3D normal;

        // Constructor
        Plane(const Math::Point3D& c, const Math::Vector3D& n) : center(c), normal(n) {}

        bool hits(const Ray& ray) const;
    };
}

#endif /* !PLANES_HPP_ */
