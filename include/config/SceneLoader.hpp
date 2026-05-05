/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneLoader header
*/

#ifndef SCENELOADER_HPP_
#define SCENELOADER_HPP_

#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include "RaytracerType.hpp"
#include "parsing.hpp"
#include "plugins/renderer/Camera.hpp"
#include "spacePartitionning/BVH.hpp"
#include "interface/ILight.hpp"
#include "design_pattern/ObjectFactory.hpp"
#include "design_pattern/MaterialFactory.hpp"

namespace Raytracer {
    class SceneLoader {
        public:
            SceneLoader(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights);
            ~SceneLoader() = default;
            void run();

        private:
            void buildScene();
            void buildShapes(std::vector<std::shared_ptr<IPrimitive>>& physical_primitives);
            void buildPlanes(std::vector<std::shared_ptr<IPrimitive>>& physical_primitives);
            void buildLights();

            void renderParallel();
            void renderLine(int j);
            void exportImage();

            Raytracer::Primitive _rawPrimitives;
            Raytracer::Camera _rawCameraInfo;
            Raytracer::Lights _rawLights;

            Raytracer::ObjectFactory _objectFactory;
            Raytracer::MaterialFactory _materialFactory;

            Raytracer::CameraClass _camera;
            std::vector<std::vector<Math::Vector3D>> _pixels;
            Raytracer::BVH _bvh;
            std::vector<std::shared_ptr<Raytracer::ILight>> _lights;

            std::mutex _renderMutex;
            int _nextLine;
    };
}

#endif /* !SCENELOADER_HPP_ */
