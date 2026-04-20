/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** PlanePrimitive
*/

#ifndef PLANE_PRIMITIVE_HPP_
#define PLANE_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"

class PlanePrimitive : public IPrimitive {
public:
    PlanePrimitive() = default;
    ~PlanePrimitive() = default;

    bool intersect(const RayTracer::Ray& ray, float t_min, float t_max, HitRecord& record) const override;
};

#endif /* !PLANE_PRIMITIVE_HPP_ */
