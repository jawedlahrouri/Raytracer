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
        private:
            std::string _name;

        public:
            IMaterial* material;
            Math::Point3D center;
            Math::Vector3D normal;
            Math::Vector3D color;

            PlanePrimitive(const Raytracer::Plane& data) : center(Math::Point3D(data.axis.X * data.positions, data.axis.Y * data.positions, data.axis.Z * data.positions)), normal(data.axis), color(data.color) {}
            ~PlanePrimitive() = default;

            bool intersect(const Raytracer::Ray& ray, HitRecord& record) const override;
            void drawShape();

            void setName(const std::string &name) override;
            void setPosition(const Math::Point3D& position) override;
            void setAxis(const Math::Vector3D& axis) override;
    };
}

#endif /* !PLANE_PRIMITIVE_HPP_ */
