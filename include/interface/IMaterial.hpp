/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "./utils/Ray.hpp"
#include "./utils/HitRecord.hpp"
#include "./interface/ILight.hpp"

class IMaterial {
    public:
        IMaterial();
        ~IMaterial();

        virtual Color getDiffuseColor(const HitRecord& record) const = 0;

    protected:
    private:
};

#endif /* !IMATERIAL_HPP_ */
