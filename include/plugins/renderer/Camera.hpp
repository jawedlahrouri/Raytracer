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

            CameraClass(double width, double height, double FieldOfView, Math::Point3D poscoords, std::map<enum Raytracer::coordType, double> rotation = {}) {
                origin = poscoords;
                double scale = width / height;
                double size_scaled = scale * 2.0;
                double projection_distance = 2.0 - (FieldOfView / 90.0);
                double projection_point = origin.Z - projection_distance;

                Math::Point3D screen_origin(origin.X - (size_scaled / 2.0), origin.Y - (2.0 / 2.0), projection_point); 
                Math::Vector3D screen_bottom(size_scaled, 0.0, 0.0);
                Math::Vector3D screen_left(0.0, 2.0, 0.0);
                if (!rotation.empty()) {
                    double rot_x = rotation.count(Raytracer::coordType::x) ? rotation.at(Raytracer::coordType::x) : 0.0;
                    double rot_y = rotation.count(Raytracer::coordType::y) ? rotation.at(Raytracer::coordType::y) : 0.0;
                    double rot_z = rotation.count(Raytracer::coordType::z) ? rotation.at(Raytracer::coordType::z) : 0.0;
                    Math::Vector3D translated_origin = origin - Math::Point3D(0, 0, 0);
                    Math::Vector3D translated_screen = screen_origin - Math::Point3D(0, 0, 0);

                    translated_origin = translated_origin.rotateX(rot_x).rotateY(rot_y).rotateZ(rot_z);
                    translated_screen = translated_screen.rotateX(rot_x).rotateY(rot_y).rotateZ(rot_z);
                    screen_bottom = screen_bottom.rotateX(rot_x).rotateY(rot_y).rotateZ(rot_z);
                    screen_left = screen_left.rotateX(rot_x).rotateY(rot_y).rotateZ(rot_z);
                    origin = Math::Point3D(0, 0, 0) + translated_origin;
                    screen_origin = Math::Point3D(0, 0, 0) + translated_screen;
                }

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
