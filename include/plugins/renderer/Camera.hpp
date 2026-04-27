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

namespace Raytracer {
    class CameraClass {
        public:
            CameraClass(double width, double height) {
                double scale = height / width;
                double size_scaled = scale * 2.0;
                Math::Point3D screen_origin(-1.0, 1.0, size_scaled / 2); // - 1 pour aller derriere, 1 pour correspondre a la moitier du bas (2) et size_scaled / 2 pour correspondre a la moitié du left qui correspondras toujours a size scaled
                Math::Vector3D screen_bottom(0.0, 2.0, 0.0);
                Math::Vector3D screen_left(0.0, 0.0, size_scaled);
                
                screen = Math::Rectangle3D(screen_origin, screen_bottom, screen_left);
            }

            ~CameraClass();

            Math::Point3D origin;
            Math::Rectangle3D screen;
            

            double u;
            double v;

            Raytracer::Ray ray(double u, double v) const {
                Math::Point3D point_on_screen = screen.pointAt(u, v);
                Math::Vector3D direction = point_on_screen - origin;
                return Raytracer::Ray(origin, direction);
            }
    };
}

#endif /* !CAMERA_HPP_ */
