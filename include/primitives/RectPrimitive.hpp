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
        Math::Point3D center;
        double width;
        double height;
        Math::Vector3D color;

        RectPrimitive(const Raytracer::Shape& data) : 
            center(data.coords), 
            width(data.specs.at(Raytracer::specsType::width)), 
            height(data.specs.at(Raytracer::specsType::height)),
            color(data.color) {}
        ~RectPrimitive()  = default;
    
        bool intersect(const Raytracer::Ray& ray, HitRecord& record) const override;
        void drawShape() override;
    };
}

#endif /* !RECT_PRIMITIVE_HPP_ */
