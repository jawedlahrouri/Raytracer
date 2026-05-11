/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Colored light
*/

#ifndef COLOREDLIGHT_HPP_
#define COLOREDLIGHT_HPP_

#include "ALight.hpp"
#include "math/Point3D.hpp"
#include "RaytracerType.hpp"
#include "parsing.hpp"

namespace Raytracer {
    class ColoredLight : public ALight {
        private:
            Math::Point3D _position;
            Math::Vector3D _color;

        public:
            ColoredLight(const Raytracer::Light& data) : _position(data.position), _color(data.lightColor) {}
            ~ColoredLight() = default;

            Math::Vector3D getDirectionToLight(const Math::Vector3D& hitPoint) const override;
            float getDistanceToLight(const Math::Vector3D& hitPoint) const override;
            Math::Vector3D calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const override;
    };
}

#endif /* !COLOREDLIGHT_HPP_ */
