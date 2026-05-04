/*
** EPITECH PROJECT, 2026
** test
** File description:
** test for the link parsing -> bootstrap
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include "./parsing.hpp"
#include "./RaytracerType.hpp"
#include "./plugins/renderer/Camera.hpp"
#include "spacePartitionning/BVH.hpp"
#include "DLLoader/load_so.hpp"
#include "design_pattern/ObjectFactory.hpp"

namespace Raytracer {
    class SfmlDisplay;

    class test {
        private:
            Raytracer::Primitive _primitive;
            Raytracer::Camera _camera;
            Raytracer::Lights _lights;

            Raytracer::CameraClass _cam;
            std::vector<std::vector<Math::Vector3D>> _pixels;
            std::vector<std::unique_ptr<DLLoader<Raytracer::IPrimitive>>> _loaders;

        public:
            test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights);
            ~test();

            void drawSphere();
            void drawPlane();
            void createScene(BVH& bvh, Raytracer::ObjectFactory& factory, SfmlDisplay* display = nullptr);
            const std::vector<std::vector<Math::Vector3D>>& getPixels() const { return _pixels; }
    };
}

#endif /* !TEST_HPP_ */
