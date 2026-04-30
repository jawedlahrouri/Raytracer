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
#include "parsing.hpp"

namespace Raytracer {
    class PointLight : public ILight {
        public:
            PointLight(const Raytracer::Light& data)
                : position(data.position), intensity_(data.intensity) {}
            PointLight(const Math::Point3D& pos, Raytracer::colorType intensity)
                : _position(pos), intensity_(intensity) {}
            ~PointLight() = default;

            Math::Vector3D getDirectionToLight(const Math::Vector3D& hitPoint) const override;
            Raytracer::colorType getIntensity() const override;
            float getDistanceToLight(const Math::Vector3D& hitPoint) const override;
            Math::Vector3D calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const override;

            void setName(const std::string &name);
            void setPosition(const Math::Point3D& position);

        private:
            std::string _name;
            Math::Point3D _position;
            Raytracer::colorType intensity_;
    };
}

#endif /* !POINTLIGHT_HPP_ */
