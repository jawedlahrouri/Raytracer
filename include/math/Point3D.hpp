/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_
#include "Vector3D.hpp"
#include <cmath>

namespace Math {
    class Point3D {
        public:
            double X;
            double Y;
            double Z;

            // Default constructor
            Point3D() : X(0), Y(0), Z(0) {}

            // Constructor with parameters
            Point3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

            // Point - Point = Vector (Ideal for: Ray.Origin - Sphere.Center)
            Vector3D operator-(const Point3D& other) const {
                return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
            }

            // Point + Vector = Point (Ideal to find the exact impact point: Origin + (Direction * t))
            Point3D operator+(const Vector3D& vec) const {
                return Point3D(X + vec.X, Y + vec.Y, Z + vec.Z);
            }

            int getX() {
                return X;
            }

            Point3D rotateX(double angle_deg) const {
                double angle_rad = angle_deg * M_PI / 180.0;
                double cos_a = std::cos(angle_rad);
                double sin_a = std::sin(angle_rad);

                return Point3D(X, Y * cos_a - Z * sin_a, Y * sin_a + Z * cos_a);
            }

            Point3D rotateY(double angle_deg) const {
                double angle_rad = angle_deg * M_PI / 180.0;
                double cos_a = std::cos(angle_rad);
                double sin_a = std::sin(angle_rad);

                return Point3D(X * cos_a + Z * sin_a, Y, -X * sin_a + Z * cos_a);
            }

            Point3D rotateZ(double angle_deg) const {
                double angle_rad = angle_deg * M_PI / 180.0;
                double cos_a = std::cos(angle_rad);
                double sin_a = std::sin(angle_rad);

                return Point3D(X * cos_a - Y * sin_a, X * sin_a + Y * cos_a, Z);
            }
        protected:
        private:
    };
} // namespace Math

#endif /* !POINT3D_HPP_ */