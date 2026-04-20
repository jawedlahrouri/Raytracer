/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** SpherePrimitive
*/

#ifndef SPHERE_PRIMITIVE_HPP_
#define SPHERE_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"
#include "./math/Point3D.hpp"
#include "./math/Vector3D.hpp"
#include "utils/Ray.hpp"
class SpherePrimitive : public IPrimitive {
public:
    Math::Point3D center;
    double radius;

    SpherePrimitive(const Math::Point3D& center, double radius);
    ~SpherePrimitive() = default;

    void sphere_logic();
    bool intersect(const RayTracer::Ray& ray, float t_min, float t_max, HitRecord& record) const override;
};

#endif /* !SPHERE_PRIMITIVE_HPP_ */
