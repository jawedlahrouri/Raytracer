/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Vector3D.hpp"

// struct light with list of points and list of d

class Ray {
    public:
        Ray();
        ~Ray();

        Vector3D origin;
        Vector3D direction;

    protected:
    private:
};

#endif /* !RAY_HPP_ */
