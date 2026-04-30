/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "Vector3D.hpp"

namespace Math {

class Point3D {
public:
    double X;
    double Y;
    double Z;

    Point3D() : X(0), Y(0), Z(0) {}
    Point3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

    // Point - Point = Vector
    Vector3D operator-(const Point3D& other) const {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    // Point + Vector = Point
    Point3D operator+(const Vector3D& vec) const {
        return Point3D(X + vec.X, Y + vec.Y, Z + vec.Z);
    }

    // Point - Vector = Point  ← celui qui manquait
    Point3D operator-(const Vector3D& vec) const {
        return Point3D(X - vec.X, Y - vec.Y, Z - vec.Z);
    }
};

} // namespace Math

#endif /* !POINT3D_HPP_ */