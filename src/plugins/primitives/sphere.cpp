/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** sphere
*/

#include "./primitives/SpherePrimitive.hpp"
#include <iostream>

void sphere_logic()
{
    std::cout << "Sphere logic placeholder" << std::endl;
    // This function is a placeholder for the logic that will handle sphere primitives in the raytracer.
    // It will likely involve calculating ray-sphere intersections and filling hit records accordingly.
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    IPrimitive* entryPoint() {
        return new SpherePrimitive();
    }
}