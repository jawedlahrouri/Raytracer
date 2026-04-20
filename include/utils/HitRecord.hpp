/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
#define HITRECORD_HPP_

#include "Vector3D.hpp"
class IMaterial;

class HitRecord {
    public:
        HitRecord();
        ~HitRecord();
        float t;              // the parameter t along the ray where the hit occurred (used to find the exact point of impact)
        Vector3D point;       //coordinates of the hit point in 3D space (x, y, z)
        Vector3D normal;      // the normal vector at the hit point (vital for lighting calculations)
        const IMaterial* material; // the material of the hit object
        
    protected:
    private:
};

#endif /* !HITRECORD_HPP_ */
