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

ILight::ILight() {}
ILight::~ILight() {}


Math::Vector3D PointLight::getDirectionToLight(const Math::Vector3D& hitPoint) const {
    Math::Vector3D dir = Math::Vector3D(position.X, position.Y, position.Z) - hitPoint;
    double len = dir.length();
    if (len == 0) return Math::Vector3D(0, 0, 0);
    return dir / len;
}

Raytracer::colorType PointLight::getIntensity() const {
    return intensity_;
}

float PointLight::getDistanceToLight(const Math::Vector3D& hitPoint) const {
    Math::Vector3D diff = Math::Vector3D(position.X, position.Y, position.Z) - hitPoint;
    return static_cast<float>(diff.length());
}

Math::Vector3D PointLight::calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const {
    Math::Vector3D toLight = getDirectionToLight(hitPoint);
    double diffuseIntensity = std::max(0.0, normal.dot(toLight));
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
}