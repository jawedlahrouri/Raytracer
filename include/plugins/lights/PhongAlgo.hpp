/*
** EPITECH PROJECT, 2026
** Raytrace
** File description:
** Phong algorithm 
*/

#ifndef PHONGALGO_HPP_
#define PHONGALGO_HPP_

#include "interface/ILight.hpp"

namespace Raytracer {
    class PhongAlgo : public ILight {
        private:

        public:
            PhongAlgo();
            ~PhongAlgo();
    };
}

#endif /* !PHONGALGO_HPP_ */
