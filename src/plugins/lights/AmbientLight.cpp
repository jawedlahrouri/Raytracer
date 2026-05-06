/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Ambient light
*/
#include <cmath>
#include <algorithm>

#include "plugins/lights/AmbientLight.hpp"

Math::Vector3D Raytracer::AmbientLight::getDirectionToLight([[maybe_unused]] const Math::Vector3D& hitPoint) const
{
    return Math::Vector3D(0, 0, 0);
}

Raytracer::colorType Raytracer::AmbientLight::getIntensity() const
{
    return Raytracer::RED;
}

float Raytracer::AmbientLight::getDistanceToLight([[maybe_unused]] const Math::Vector3D& hitPoint) const
{
    return std::numeric_limits<float>::max();
}

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
