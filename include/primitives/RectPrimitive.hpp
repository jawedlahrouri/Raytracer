/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** CubePrimitive
*/

#ifndef RECT_PRIMITIVE_HPP_
#define RECT_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"

class RectPrimitive : public IPrimitive {
public:
    RectPrimitive() = default;
    ~RectPrimitive()  = default;

    bool intersect(const RayTracer::Ray& ray, float t_min, float t_max, HitRecord& record) const override;
};

#endif /* !RECT_PRIMITIVE_HPP_ */
