/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Ambient Light
*/

#ifndef AMBIENTLIGHT_HPP_
#define AMBIENTLIGHT_HPP_

#include "interface/ILight.hpp"
#include "math/Point3D.hpp"
#include "RaytracerType.hpp"
#include "parsing.hpp"

namespace Raytracer {
    class AmbientLight : public ILight {
        private:
            float _intensity;

        public:
            AmbientLight(const Raytracer::Light& data) : _intensity(data.ambientIntensity) {}
            ~AmbientLight() = default;

            Math::Vector3D getDirectionToLight(const Math::Vector3D& hitPoint) const override;
            Raytracer::colorType getIntensity() const override;
            float getDistanceToLight(const Math::Vector3D& hitPoint) const override;
            bool canLightBeBlocked() const override;
            Math::Vector3D calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const override;
    };
}

#endif /* !AMBIENTLIGHT_HPP_ */
