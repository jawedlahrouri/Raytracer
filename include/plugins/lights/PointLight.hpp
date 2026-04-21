/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "interface/ILight.hpp"
#include "math/Point3D.hpp"
#include "RaytracerType.hpp"

class PointLight : public ILight {
public:
    PointLight(const Math::Point3D& pos, Raytracer::colorType intensity)
        : position(pos), intensity_(intensity) {}
    ~PointLight() = default;

    Math::Vector3D getDirectionToLight(const Math::Vector3D& hitPoint) const override;
    Raytracer::colorType getIntensity() const override;
    float getDistanceToLight(const Math::Vector3D& hitPoint) const override;

private:
    Math::Point3D position;
    Raytracer::colorType intensity_;
};

#endif /* !POINTLIGHT_HPP_ */
