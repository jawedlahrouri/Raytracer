/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Vector3D
*/


#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_
#include <cmath>

namespace Math {
    class Vector3D {
    public:
        double X;
        double Y;
        double Z;

        // Default constructor
        Vector3D() : X(0), Y(0), Z(0) {}

        // Constructor with parameters
        Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

        // Length (norm) of the vector
        double length() const {
            return std::sqrt(X * X + Y * Y + Z * Z);
        }

        // Dot product
        double dot(const Vector3D& other) const {
            return X * other.X + Y * other.Y + Z * other.Z;
        }

        // Vector * scalar (e.g.: Direction * t)
        Vector3D operator*(double scalar) const {
            return Vector3D(X * scalar, Y * scalar, Z * scalar);
        }

        // Vector / scalar (e.g.: divide by radius for normal)
        Vector3D operator/(double scalar) const {
            return Vector3D(X / scalar, Y / scalar, Z / scalar);
        }

        // Vector - Vector
        Vector3D operator-(const Vector3D& other) const {
            return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
        }
        
        // Vector + Vector
        Vector3D operator+(const Vector3D& other) const {
            return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
        }

        Vector3D cross(const Vector3D& other) const {
            return Vector3D(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X            );
        }

        Vector3D rotateX(double angle_deg) const {
            double angle_rad = angle_deg * M_PI / 180.0;
            double cos_a = std::cos(angle_rad);
            double sin_a = std::sin(angle_rad);

            return Vector3D(X, Y * cos_a - Z * sin_a, Y * sin_a + Z * cos_a);
        }

        Vector3D rotateY(double angle_deg) const {
            double angle_rad = angle_deg * M_PI / 180.0;
            double cos_a = std::cos(angle_rad);
            double sin_a = std::sin(angle_rad);

            return Vector3D(X * cos_a + Z * sin_a, Y, -X * sin_a + Z * cos_a
            );
        }

        Vector3D rotateZ(double angle_deg) const {
            double angle_rad = angle_deg * M_PI / 180.0;
            double cos_a = std::cos(angle_rad);
            double sin_a = std::sin(angle_rad);

            return Vector3D(X * cos_a - Y * sin_a, X * sin_a + Y * cos_a, Z);
        }
    };
}

#endif /* !VECTOR3D_HPP_ */
