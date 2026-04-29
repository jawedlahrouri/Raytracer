/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** SpherePrimitive
*/

#ifndef SPHERE_PRIMITIVE_HPP_
#define SPHERE_PRIMITIVE_HPP_

#include "./interface/IPrimitive.hpp"
#include "./parsing.hpp"
#include "./math/Point3D.hpp"
#include "./math/Vector3D.hpp"
#include "utils/Ray.hpp"

namespace Raytracer {
    class SpherePrimitive : public IPrimitive {
        private:
            std::string _name;

        public:
            Math::Point3D center;
            double radius;
            Math::Vector3D color;

            SpherePrimitive(const Raytracer::Shape& data) : center(data.coords), radius(data.specs.at(Raytracer::specsType::r)), color(data.color) {}
            ~SpherePrimitive() = default;

            void sphere_logic();
            bool intersect(const Raytracer::Ray& ray, HitRecord& record) const override;
            void drawShape();

            void setName(const std::string &name) override;
            void setPosition(const Math::Point3D& position) override;
    };
}

#endif /* !SPHERE_PRIMITIVE_HPP_ */
