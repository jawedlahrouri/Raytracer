/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "./math/Vector3D.hpp"

namespace RayTracer {
    class Ray {
        public:
        Ray(const Math::Vector3D& origin = Math::Vector3D(0, 0, 0), const Math::Vector3D& direction = Math::Vector3D(0, 0, 0));
        ~Ray();
        
        Math::Vector3D origin;
        Math::Vector3D direction;

        protected:
        private:
    };
}

#endif /* !RAY_HPP_ */
