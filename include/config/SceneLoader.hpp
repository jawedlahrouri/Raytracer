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
#include "display/sfml_display.hpp"
#include "utils/Progress.hpp"

namespace Raytracer {
    class SceneLoader {
        public:
            SceneLoader(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights);
            ~SceneLoader() = default;
            void run(Raytracer::SfmlDisplay* display = nullptr);
            void setAALevel(int level) { _aaLevel = level; }

        private:
            void buildScene();
            void buildShapes(std::vector<std::shared_ptr<IPrimitive>>& physical_primitives);
            void buildPlanes(std::vector<std::shared_ptr<IPrimitive>>& physical_primitives);
            void buildPointLight();
            void buildDirectionalLight();
            void buildAmbientLight();

            void renderParallel(Raytracer::SfmlDisplay* display);
            void renderLine(int j, Raytracer::SfmlDisplay* display);
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
            
            Math::Vector3D computeRayColor(double u, double v);
            int _aaLevel = 0;
            double _aaThreshold = 0.1;
    };
}

#endif /* !SCENELOADER_HPP_ */
