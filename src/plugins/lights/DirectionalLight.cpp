/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Directional Light
*/
#include <cmath>
#include <algorithm>

#include "plugins/lights/DirectionalLight.hpp"
#include "interface/ILight.hpp"

Math::Vector3D Raytracer::DirectionalLight::getDirectionToLight([[maybe_unused]] const Math::Vector3D& hitPoint) const
{
    return _direction;
}

Raytracer::colorType Raytracer::DirectionalLight::getIntensity() const
{
    return _intensity;
}

float Raytracer::DirectionalLight::getDistanceToLight([[maybe_unused]] const Math::Vector3D& hitPoint) const
{
    return std::numeric_limits<float>::max();
}

bool Raytracer::DirectionalLight::canLightBeBlocked() const
{
    return true;
}

Math::Vector3D Raytracer::DirectionalLight::calculateIllumination([[maybe_unused]] const Math::Vector3D& hitPoint,
    const Math::Vector3D& normal, const Math::Vector3D& baseColor) const
{
    double diffuseIntensity = std::max(0.0, normal.dot(_direction));

    return Math::Vector3D(
        baseColor.X * diffuseIntensity,
        baseColor.Y * diffuseIntensity,
        baseColor.Z * diffuseIntensity
    );
}

extern "C" {
    int getType()
    {
        return 1; // 1 for lights
    }

    Raytracer::ILight* entryPoint(const Raytracer::Light& data) {
        return new Raytracer::DirectionalLight(data);
    }
}
