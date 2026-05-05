/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
#define HITRECORD_HPP_

#include "./math/Vector3D.hpp"
#include "math/Point3D.hpp"
#include "utils/Ray.hpp"

namespace Raytracer { class IMaterial; }

class HitRecord {
    public:
        HitRecord() : t(0), u(0), v(0), point(0,0,0), normal(0,0,0), color(0,0,0), material(nullptr) {}
        ~HitRecord() = default;
        double t;
        double u;
        double v;
        Raytracer::Ray ray;
        Math::Point3D point;
        Math::Vector3D normal;
        Math::Vector3D color;
        const Raytracer::IMaterial* material;
};

#endif /* !HITRECORD_HPP_ */