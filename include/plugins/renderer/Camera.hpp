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
#include <map>
#include "RaytracerType.hpp"
#include "./utils/Ray.hpp"

namespace Raytracer {
    class CameraClass {
        public:
            Math::Point3D origin;
            Math::Rectangle3D screen;

            CameraClass(double width, double height, double FieldOfView, Math::Point3D poscoords) {
                origin = poscoords;
                double scale = width / height;
                double size_scaled = scale * 2.0;
                double projection_distance = (FieldOfView/90) - 2;
                double projection_point = origin.Z - projection_distance;

                Math::Point3D screen_origin(origin.X - (size_scaled / 2.0), origin.Y - (2.0 / 2.0), projection_point); 
                Math::Vector3D screen_bottom(size_scaled, 0.0, 0.0);
                Math::Vector3D screen_left(0.0, 2.0, 0.0);
                
                screen = Math::Rectangle3D(screen_origin, screen_bottom, screen_left);
            }

            ~CameraClass();

            Raytracer::Ray ray(double u, double v) const {
                Math::Point3D point_on_screen = screen.pointAt(u, v);
                Math::Vector3D direction = point_on_screen - origin;
                return Raytracer::Ray(origin, direction);
            }
    };
}

#endif /* !CAMERA_HPP_ */
