/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AABB for BVH algorithm for space partitionning
*/

#ifndef AABB_HPP_
#define AABB_HPP_

#include "./math/Vector3D.hpp"
#include "./RaytracerType.hpp"
#include "./utils/Ray.hpp"
#include <iostream>
#include <bits/stdc++.h>

namespace Raytracer {
    class AABB {
    private:

    public:
        Math::Vector3D min;
        Math::Vector3D max;

        AABB() = default;
        ~AABB() = default;

        bool intersect(const Ray& ray, double tMin, double tMax) const;
        float surfaceArea() const;
        static AABB merge(const AABB& a, const AABB& b) {
            AABB result;
            result.min = Math::Vector3D(
                std::min(a.min.X, b.min.X),
                std::min(a.min.Y, b.min.Y),
                std::min(a.min.Z, b.min.Z)
            );
            result.max = Math::Vector3D(
                std::max(a.max.X, b.max.X),
                std::max(a.max.Y, b.max.Y),
                std::max(a.max.Z, b.max.Z)
            );
            return result;
        }
};
}

#endif /* !AABB_HPP_ */
