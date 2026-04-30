/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Shadow_Ray
*/

#ifndef SHADOW_RAY_HPP_
#define SHADOW_RAY_HPP_

#include "utils/HitRecord.hpp"
#include "utils/Ray.hpp"
#include "primitives/SpherePrimitive.hpp"
#include "primitives/PlanePrimitive.hpp"

namespace Raytracer {
    class Shadow_Ray {
        public:
            Shadow_Ray() = default;
            ~Shadow_Ray() = default;
    
            // check if the ray hits
            bool hits(const Raytracer::Ray& ray, const Raytracer::SpherePrimitive& s, const Raytracer::PlanePrimitive& p) const;
    };
}

#endif /* !SHADOW_RAY_HPP_ */
