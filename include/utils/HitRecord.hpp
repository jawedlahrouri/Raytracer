/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
#define HITRECORD_HPP_

#include "./math/Vector3D.hpp"
class IMaterial;

class HitRecord {
    public:
        HitRecord() : t(0), u(0), v(0), point(0,0,0), normal(0,0,0), color(0,0,0), material(nullptr) {}
        ~HitRecord() = default;
        double t;
        double u;
        double v;
        Math::Vector3D point;        //coordinates of the hit point in 3D space (x, y, z)
        Math::Vector3D normal;     // the normal vector at the hit point (vital for lighting calculations)
        Math::Vector3D color;        // the base color of the hit object
        const IMaterial* material; // the material of the hit object

    protected:
    private:
};

#endif /* !HITRECORD_HPP_ */
