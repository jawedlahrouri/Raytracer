/*
** EPITECH PROJECT, 2026
** test
** File description:
** test for the link parsing -> bootstrap
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include "../parsing.hpp"
#include "../RaytracerType.hpp"

namespace Raytracer {
    class test {
        private:
            Raytracer::Primitive _primitive;
            Raytracer::Camera _camera;
            Raytracer::Lights _lights;

        public:
            test (Raytracer::Primitive primitive, Raytracer::Camera camera, Raytracer::Lights lights);
            ~test();

            void drawShape();
            void drawPlane();
            void createScene();
    };
}

#endif /* !TEST_HPP_ */
