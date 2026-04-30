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
#include "./RaytracerType.hpp"
#include "./spacePartitionning/AABB.hpp"

namespace Raytracer {
    class IPrimitive  {
        public:
            virtual ~IPrimitive() = default;

            // Check if the ray intersects with the primitive and fill the hit record if it does
            virtual bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const = 0;
            virtual AABB bounds() const = 0;
            virtual Math::Point3D centroid() const = 0;

        protected:
        private:
    };
}

#endif /* !IPRIMITIVE_HPP_ */
