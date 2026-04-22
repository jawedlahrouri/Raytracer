/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** planes
*/

#include "./primitives/PlanePrimitive.hpp"

void plane_logic()
{
    // This function is a placeholder for the logic that will handle plane primitives in the raytracer.
    // It will likely involve calculating ray-plane intersections and filling hit records accordingly.
}

extern "C" {
    int getType()
    {
        return 0; // 0 for primitives
    }

    IPrimitive* entryPoint() {
        return new PlanePrimitive();
    }
}