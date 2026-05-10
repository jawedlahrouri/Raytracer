/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Colored light
*/
#include "plugins/lights/ColoredLight.hpp"

Math::Vector3D Raytracer::ColoredLight::getDirectionToLight(const Math::Vector3D& hitPoint) const
{
    Math::Vector3D dir = Math::Vector3D(_position.X, _position.Y, _position.Z) - hitPoint;
    double len = dir.length();

    if (len == 0)
        return Math::Vector3D(0, 0, 0);
    return dir / len;
}

Raytracer::colorType Raytracer::ColoredLight::getIntensity() const
{
    return Raytracer::RED;
}

float Raytracer::ColoredLight::getDistanceToLight(const Math::Vector3D& hitPoint) const
{
    Math::Vector3D diff = Math::Vector3D(_position.X, _position.Y, _position.Z) - hitPoint;

    return static_cast<float>(diff.length());
}

bool Raytracer::ColoredLight::canLightBeBlocked() const
{
    return true;
}

Math::Vector3D Raytracer::ColoredLight::calculateIllumination(const Math::Vector3D& hitPoint,
    const Math::Vector3D& normal, const Math::Vector3D& baseColor) const
{
    Math::Vector3D toLight = getDirectionToLight(hitPoint);
    double diffuseIntensity = std::max(0.0, normal.dot(toLight));

    return Math::Vector3D(
        baseColor.X * (_color.X / 255.0) * diffuseIntensity,
        baseColor.Y * (_color.Y / 255.0) * diffuseIntensity,
        baseColor.Z * (_color.Z / 255.0) * diffuseIntensity
    );
}

extern "C" {
    int getType()
    {
        return 1; // 1 for lights
    }

    Raytracer::ILight* entryPoint(const Raytracer::Light& data) {
        return new Raytracer::ColoredLight(data);
    }
}
