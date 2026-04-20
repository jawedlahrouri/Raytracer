/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_
#include "./utils/Vector3D.hpp"
#include "./RaytracerType.hpp"

class ILight {
    public:
        ILight();
        ~ILight();

        // Get the direction from the hit point to the light source
        virtual Vector3D getDirectionToLight(const Vector3D& hitPoint) const = 0;

        // Get the intensity of the light at the hit point
        virtual Raytracer::colorType getIntensity() const = 0;

        // Get the distance from the hit point to the light source (for shadow calculations)
        virtual float getDistanceToLight(const Vector3D& hitPoint) const = 0;

    protected:
    private:
};

#endif /* !ILIGHT_HPP_ */
