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
#include "../plugins/renderer/Camera.hpp"

namespace Raytracer {
    class test {
        private:
            Raytracer::Primitive _primitive;
            Raytracer::Camera _camera;
            Raytracer::Lights _lights;

            Raytracer::CameraClass _cam;
            std::vector<std::vector<Math::Vector3D>> _pixels;

        public:
            test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights);
            ~test();

            void drawSphere();
            void drawPlane();
            void createScene();
    };
}

#endif /* !TEST_HPP_ */
