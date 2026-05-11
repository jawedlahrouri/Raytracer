/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Ambient light
*/
#include <cmath>
#include <algorithm>

#include "plugins/lights/AmbientLight.hpp"

bool Raytracer::AmbientLight::canLightBeBlocked() const
{
    return false;
}

Math::Vector3D Raytracer::AmbientLight::calculateIllumination([[maybe_unused]] const Math::Vector3D& hitPoint,
    [[maybe_unused]] const Math::Vector3D& normal, const Math::Vector3D& baseColor) const
{
    return Math::Vector3D(
        baseColor.X * _intensity,
        baseColor.Y * _intensity,
        baseColor.Z * _intensity
    );
}

extern "C" {
    int getType()
    {
        return 1; // 1 for lights
    }

    Raytracer::ILight* entryPoint(const Raytracer::Light& data) {
        return new Raytracer::AmbientLight(data);
    }
}
