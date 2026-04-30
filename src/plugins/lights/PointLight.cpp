/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** PointLight implementation
*/

#include "plugins/lights/PointLight.hpp"
#include <cmath>
#include <algorithm>
#include "exception.hpp"
#include "interface/ILight.hpp"

Math::Vector3D Raytracer::PointLight::getDirectionToLight(const Math::Vector3D& hitPoint) const {
    Math::Vector3D dir = Math::Vector3D(_position.X, _position.Y, _position.Z) - hitPoint;
    double len = dir.length();
    if (len == 0) return Math::Vector3D(0, 0, 0);
    return dir / len;
}

Raytracer::colorType Raytracer::PointLight::getIntensity() const {
    return _intensity;
}

float Raytracer::PointLight::getDistanceToLight(const Math::Vector3D& hitPoint) const {
    Math::Vector3D diff = Math::Vector3D(_position.X, _position.Y, _position.Z) - hitPoint;
    return static_cast<float>(diff.length());
}

Math::Vector3D Raytracer::PointLight::calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const {
    Math::Vector3D toLight = getDirectionToLight(hitPoint);
    double diffuseIntensity = std::max(0.0, normal.dot(toLight));
    return Math::Vector3D(
        baseColor.X * diffuseIntensity,
        baseColor.Y * diffuseIntensity,
        baseColor.Z * diffuseIntensity
    );
}

void Raytracer::PointLight::setName(const std::string &name)
{
    _name = name;
}

void Raytracer::PointLight::setPosition(const Math::Point3D& position)
{
    _position = position;
}

extern "C" {
    int getType()
    {
        return 1; // 1 for lights
    }

    Raytracer::ILight* entryPoint() {
        return new Raytracer::PointLight(Math::Point3D(0, 0, 0), Raytracer::RED);
    }
}