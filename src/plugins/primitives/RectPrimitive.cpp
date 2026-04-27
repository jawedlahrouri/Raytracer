/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#include "./primitives/RectPrimitive.hpp"

void rect_logic()
{
    // This function is a placeholder for the logic that will handle rectangle primitives in the raytracer.
    // It will likely involve calculating ray-rectangle intersections and filling hit records accordingly.
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    Raytracer::IPrimitive* entryPoint() {
        return new Raytracer::RectPrimitive();
    }
}