/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ConePrimitive
*/

#ifndef CONE_PRIMITIVE_HPP_
#define CONE_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"
#include "./exception.hpp"
#include "./parsing.hpp"
#include <cmath>

namespace Raytracer {
    class ConePrimitive : public IPrimitive {
    public:
        Math::Point3D center;
        double height;
        double radius;
        Math::Vector3D color;
        Math::Vector3D _rotation;

        ConePrimitive(const Raytracer::Shape& data) : 
            center(data.coords), 
            height(data.specs.at(Raytracer::specsType::height)),
            radius(data.specs.at(Raytracer::specsType::r)),
            color(data.color),
            _rotation(data.rotation) {}
        ~ConePrimitive() = default;

        bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;
        AABB bounds() const override;
        Math::Point3D centroid() const override;
    };
}

#endif /* !CONE_PRIMITIVE_HPP_ */
