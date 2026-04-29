/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_
#include "./utils/Ray.hpp"
#include "./utils/HitRecord.hpp"
#include "RaytracerType.hpp"

#include <iostream>

namespace Raytracer {
    class IPrimitive  {
        public:
            IPrimitive();
            virtual ~IPrimitive() = default;

            // Check if the ray intersects with the primitive and fill the hit record if it does
            virtual bool intersect(const Raytracer::Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;

            virtual void drawShape() = 0;

            virtual void setName(std::string name);
            virtual bool hits(const Raytracer::Ray& ray, HitRecord& record) const = 0;
            virtual void setPosition(double x, double y, double z) = 0;
            virtual void setAxis(double x, double y, double z) = 0;
            
        protected:
        private:
    };
}

#endif /* !IPRIMITIVE_HPP_ */
