/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** CubePrimitive
*/

#ifndef RECT_PRIMITIVE_HPP_
#define RECT_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"
#include "./exception.hpp"
#include "./parsing.hpp"
#include "./math.h"

namespace Raytracer {
    class RectPrimitive : public IPrimitive {
    public:
        RectPrimitive(const Raytracer::Shape& data) {} // a modifier avec les bon variables et les bonne valeur qui seront dans shape
        ~RectPrimitive()  = default;
    
        bool intersect(const Raytracer::Ray& ray, HitRecord& record) const override;
        void drawShape();
    };
}

#endif /* !RECT_PRIMITIVE_HPP_ */
