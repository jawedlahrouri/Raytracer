/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

#include "math/Point3D.hpp"
#include <cmath>
#include "./utils/Ray.hpp"
#include "./utils/HitRecord.hpp"
#include "math/Vector3D.hpp"

namespace Raytracer {
    class Rect {
    public:
        Math::Point3D center;
        Math::Vector3D normal;
        Math::Vector3D color;

        // Constructor
        Rect(const Math::Point3D& c, const Math::Vector3D& n, const Math::Vector3D& col = Math::Vector3D(0, 0, 255)) : center(c), normal(n), color(col) {}

        bool hits(const Ray& ray, HitRecord& rec) const;
    };
}

#endif /* !RECT_HPP_ */
