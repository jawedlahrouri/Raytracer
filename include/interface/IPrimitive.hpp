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

namespace Raytracer {
    class IPrimitive  {
        public:
            IPrimitive();
            ~IPrimitive();

            // Check if the ray intersects with the primitive and fill the hit record if it does
            virtual bool intersect(const Raytracer::Ray& ray, HitRecord& record) const = 0;

            virtual void drawShape() = 0;

        protected:
        private:
    };
}

#endif /* !IPRIMITIVE_HPP_ */
