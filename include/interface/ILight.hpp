/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_
#include "./math/Vector3D.hpp"
#include "./RaytracerType.hpp"

#include <string>

namespace Raytracer {
    class ILight {
        public:
            ILight();
            ~ILight();

            // Get the direction from the hit point to the light source
            virtual Math::Vector3D getDirectionToLight(const Math::Vector3D& hitPoint) const = 0;

            // Get the intensity of the light at the hit point
            virtual Raytracer::colorType getIntensity() const = 0;

            // Get the distance from the hit point to the light source (for shadow calculations)
            virtual float getDistanceToLight(const Math::Vector3D& hitPoint) const = 0;

            // Calculate illumination color
            virtual Math::Vector3D calculateIllumination(const Math::Vector3D& hitPoint, const Math::Vector3D& normal, const Math::Vector3D& baseColor) const = 0;

            virtual void setName(std::string name);
        protected:
        private:
    };
}

#endif /* !ILIGHT_HPP_ */
