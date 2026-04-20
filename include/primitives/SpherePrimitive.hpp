/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** SpherePrimitive
*/

#ifndef SPHERE_PRIMITIVE_HPP_
#define SPHERE_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"

class SpherePrimitive : public IPrimitive {
public:
    SpherePrimitive() = default;
    ~SpherePrimitive() = default;

    bool intersect(const Ray& ray, float t_min, float t_max, HitRecord& record) const override;
};

#endif /* !SPHERE_PRIMITIVE_HPP_ */
