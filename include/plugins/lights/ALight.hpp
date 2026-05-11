/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Abstract class for lights
*/

#ifndef ALIGHT_HPP_
#define ALIGHT_HPP_

#include "interface/ILight.hpp"

namespace Raytracer {
    class ALight : public ILight {
        public:
            Math::Vector3D getDirectionToLight([[maybe_unused]] const Math::Vector3D& hitPoint) const override
            {
                return Math::Vector3D(0, 0, 0);
            }

            Raytracer::colorType getIntensity() const override
            {
                return Raytracer::RED;
            }

            float getDistanceToLight([[maybe_unused]] const Math::Vector3D& hitPoint) const override
            {
                return std::numeric_limits<float>::max();
            }

            Math::Vector3D calculateIllumination([[maybe_unused]] const Math::Vector3D& hitPoint, [[maybe_unused]] const Math::Vector3D& normal, [[maybe_unused]] const Math::Vector3D& baseColor) const override
            {
                return Math::Vector3D(0,  0, 0);
            }

            bool canLightBeBlocked() const override
            {
                return true;
            }
    };
}

#endif /* !ALIGHT_HPP_ */
