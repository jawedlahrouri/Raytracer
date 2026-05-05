/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include "interface/ILight.hpp"
#include "math/Point3D.hpp"
#include "RaytracerType.hpp"
#include "parsing.hpp"

namespace Raytracer {
    class DirectionalLight : public ILight {
        private:
            Math::Vector3D _direction;
            Raytracer::colorType _intensity;

        public:
            DirectionalLight(const Raytracer::Light& data) : _direction(data.direction.X, data.direction.Y, data.direction.Z), _intensity(data.intensity)
            {
                double len = _direction.length();
                if (len > 0) {
                    _direction = _direction / len;
                }
            }
            ~DirectionalLight() = default;

            Math::Vector3D getDirectionToLight(const Math::Vector3D& hitPoint) const override;
            Raytracer::colorType getIntensity() const override;
            float getDistanceToLight(const Math::Vector3D& hitPoint) const override;
            Math::Vector3D calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const override;
    };
}

#endif /* !DIRECTIONALLIGHT_HPP_ */
