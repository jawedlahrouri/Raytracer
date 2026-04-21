/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"
#include "math/Rectangle3D.hpp"
#include "./utils/Ray.hpp"

namespace RayTracer {
    class Camera {
        public:
        Camera() : origin (0, 0, 0) {
            Math::Point3D screen_origin(-1.0, -1.0, 1.0);
            Math::Vector3D screen_bottom(2.0, 0.0, 0.0);
            Math::Vector3D screen_left(0.0, 2.0, 0.0);
            
            screen = Math::Rectangle3D(screen_origin, screen_bottom, screen_left);
        }

        ~Camera();

        Math::Point3D origin;
        Math::Rectangle3D screen;

        double u;
        double v;

        RayTracer::Ray ray(double u, double v) const {
            Math::Point3D point_on_screen = screen.pointAt(u, v);
            Math::Vector3D direction = point_on_screen - origin;
            return RayTracer::Ray(origin, direction);
        }
    };
}

#endif /* !CAMERA_HPP_ */
