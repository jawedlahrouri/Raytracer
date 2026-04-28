/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** CubePrimitive
*/

#ifndef RECT_PRIMITIVE_HPP_
#define RECT_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"

namespace Raytracer {
    class RectPrimitive : public IPrimitive {
    public:
        RectPrimitive() = default;
        ~RectPrimitive()  = default;
    
        bool intersect(const Raytracer::Ray& ray, float t_min, float t_max, HitRecord& record) const override;
        void drawShape();
    };
}

#endif /* !RECT_PRIMITIVE_HPP_ */
