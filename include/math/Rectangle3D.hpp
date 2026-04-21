/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP_
#define RECTANGLE3D_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Math {
    class Rectangle3D {
        public:
        Point3D origin;
        Vector3D bottom_side;
        Vector3D left_side;
        
        Rectangle3D() = default;
        Rectangle3D(Point3D o, Vector3D bottom, Vector3D left) 
            : origin(o), bottom_side(bottom), left_side(left) {}

        Point3D pointAt(double u, double v) const {
            return origin + (bottom_side * u) + (left_side * v);
        }
    protected:
    private:
};
}

#endif /* !RECTANGLE3D_HPP_ */
