/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "./math/Vector3D.hpp"
#include "./math/Point3D.hpp"

namespace RayTracer {
    class Ray {
        public:
        Ray(const Math::Point3D& origin = Math::Point3D(), const Math::Vector3D& direction = Math::Vector3D());
        ~Ray();
        
        Math::Point3D origin;
        Math::Vector3D direction;

        protected:
        private:
    };
}

#endif /* !RAY_HPP_ */
