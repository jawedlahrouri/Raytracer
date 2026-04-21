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
        HitRecord();
        ~HitRecord();
        double t;
        Math::Vector3D point;       //coordinates of the hit point in 3D space (x, y, z)
        Math::Vector3D normal;      // the normal vector at the hit point (vital for lighting calculations)
        const IMaterial* material; // the material of the hit object

    protected:
    private:
};

#endif /* !HITRECORD_HPP_ */
