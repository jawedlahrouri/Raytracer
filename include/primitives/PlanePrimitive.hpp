/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** PlanePrimitive
*/

#ifndef PLANE_PRIMITIVE_HPP_
#define PLANE_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"
#include "./exception.hpp"
#include "./parsing.hpp"
#include "./math.h"

namespace Raytracer {
    class PlanePrimitive : public IPrimitive {
        public:
            Math::Point3D center;
            Math::Vector3D normal;
            Math::Vector3D color;

            PlanePrimitive(const Raytracer::Plane& data) : center(Math::Point3D(0, 0, data.positions)), normal(Math::Vector3D()) {}
            ~PlanePrimitive() = default;

            bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;
            AABB bounds() const override;
            Math::Point3D centroid() const override;
    };
}

#endif /* !PLANE_PRIMITIVE_HPP_ */
