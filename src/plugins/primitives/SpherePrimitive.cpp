/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** sphere
*/

#include "./primitives/SpherePrimitive.hpp"


//constructor setup
SpherePrimitive::SpherePrimitive(const Math::Point3D& _center, double _radius) {
    center = _center;
    radius = _radius;
}

void SpherePrimitive::sphere_logic()
{
    // This function is a placeholder for the logic that will handle sphere primitives in the raytracer.
    // It will likely involve calculating ray-sphere intersections and filling hit records accordingly.
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    IPrimitive* entryPoint() {
        Math::Point3D center(0, 0, 0);
        return new SpherePrimitive(center, 1.0); // Example: create a sphere at the origin with radius 1
    }
}