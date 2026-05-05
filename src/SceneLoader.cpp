/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneLoader implementation - Modular version
*/

#include "SceneLoader.hpp"
#include "design_pattern/MaterialFactory.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "utils/HitRecord.hpp"
#include "exception.hpp"
#include <iostream>
#include <limits>

Raytracer::SceneLoader::SceneLoader(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights)
    : _rawPrimitives(primitive), _rawCameraInfo(camera), _rawLights(lights),
    _camera(camera.size.first, camera.size.second, camera.fieldOfView, camera.posCoords, camera.rotaCoords),
    _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first)),
    _nextLine(0)
{
}

void Raytracer::SceneLoader::run()
{
    try {
        buildScene();
        renderParallel();
        exportImage();
    } catch (const Exception& e) {
        std::cerr << "Critical Error: " << e.what() << std::endl;
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected System Error: " << e.what() << std::endl;
        throw CrashException(std::string("Internal crash: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildScene()
{
    try {
        std::vector<std::shared_ptr<Raytracer::IPrimitive>> physical_primitives;

        buildShapes(physical_primitives);
        buildPlanes(physical_primitives);
        buildLights();

        if (physical_primitives.empty())
            throw WarningException("Scene building: No objects found.");

        _bvh.build(std::move(physical_primitives));
    } catch (const Exception& e) {
        throw;
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Build process failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildShapes(std::vector<std::shared_ptr<IPrimitive>>& physical_primitives)
{
    try {
        for (const auto& [name, shapeData] : _rawPrimitives.listOfShapes) {
            auto prim = _objectFactory.createPrimitive(shapeData.type, shapeData);
            if (prim) {
                prim->material = _materialFactory.createMaterial(shapeData.material);
                physical_primitives.push_back(prim);
            }
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Shapes instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildPlanes(std::vector<std::shared_ptr<IPrimitive>>& physical_primitives)
{
    try {
        for (const auto& [name, planeData] : _rawPrimitives.listOfPlane) {
            auto newPlane = _objectFactory.createPrimitive("Plane", planeData);   
            if (newPlane) {
                newPlane->material = _materialFactory.createMaterial(planeData.material);
                physical_primitives.push_back(newPlane);
            }
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Planes instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildLights()
{
    try {
        for (const auto& [id, pos] : _rawLights.listPoints) {
            Raytracer::Light data;
            data.position = pos;
            data.intensity = Raytracer::RED;
            
            auto newLight = _objectFactory.createLight("Point", data);
            if (newLight) _lights.push_back(newLight);
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Lights instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::renderParallel()
{
    try {
        _nextLine = 0;
        unsigned int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) num_threads = 1;
        
        std::vector<std::thread> threads;

        auto worker = [&]() {
            try {
                while (true) {
                    int j;
                    {
                        std::lock_guard<std::mutex> lock(_renderMutex);
                        if (_nextLine >= (int)_rawCameraInfo.size.second)
                            return;
                        j = _nextLine++;
                    }
                    renderLine(j);
                }
            } catch (const std::exception& e) {
                std::lock_guard<std::mutex> lock(_renderMutex);
                std::cerr << "Thread error: " << e.what() << std::endl;
            }
        };

        for (unsigned int i = 0; i < num_threads; ++i)
            threads.emplace_back(worker);

        for (auto& t : threads)
            t.join();

    } catch (const std::exception& e) {
        throw CrashException(std::string("Parallel rendering crashed: ") + e.what());
    }
}

void Raytracer::SceneLoader::renderLine(int j)
{
    try {
        int width = (int)_rawCameraInfo.size.first;
        int height = (int)_rawCameraInfo.size.second;

        for (int i = 0; i < width; i++) {
            double u = static_cast<double>(i) / (width - 1);
            double v = static_cast<double>(j) / (height - 1);
            Raytracer::Ray r = _camera.ray(u, v);

            Math::Vector3D pixel_color(0, 0, 0);
            HitRecord rec;
            
            if (_bvh.intersect(r, 0.001f, 1e9f, rec)) {
                if (rec.material && !_lights.empty()) {
                    pixel_color = rec.material->getDiffuseColor(rec, _lights, _bvh);
                    pixel_color = Math::Vector3D(pixel_color.X / 255.0, pixel_color.Y / 255.0, pixel_color.Z / 255.0);
                } else {
                    pixel_color = Math::Vector3D(rec.color.X / 255.0, rec.color.Y / 255.0, rec.color.Z / 255.0);
                }
            }
            _pixels[j][i] = pixel_color;
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Failed to render line ") + std::to_string(j) + ": " + e.what());
    }
}

void Raytracer::SceneLoader::exportImage()
{
    try {
        Raytracer::PPMExporter exporter;
        exporter.write_image((int)_rawCameraInfo.size.first, (int)_rawCameraInfo.size.second, _pixels);
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Image export failed: ") + e.what());
    }
}
