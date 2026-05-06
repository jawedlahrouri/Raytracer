/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneLoader implementation - Modular version
*/

#include "config/SceneLoader.hpp"
#include "design_pattern/MaterialFactory.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "utils/HitRecord.hpp"
#include "optical_effects/Antialazing.hpp"
#include "exception.hpp"
#include <iostream>
#include <limits>
#include <chrono>
#include <iomanip>

Raytracer::SceneLoader::SceneLoader(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights)
    : _rawPrimitives(primitive), _rawCameraInfo(camera), _rawLights(lights),
    _camera(camera.size.first, camera.size.second, camera.fieldOfView, camera.posCoords, camera.rotaCoords),
    _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first)),
    _nextLine(0)
{
}

void Raytracer::SceneLoader::run(Raytracer::SfmlDisplay* display)
{
    try {
        buildScene();
        if (display) {
            std::thread renderThread([this, display]() {
                renderParallel(display);
            });
            while (display->isOpen() && !display->shouldExport()) {
                display->refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
                bool done = false;
                {
                    std::lock_guard<std::mutex> lock(_renderMutex);
                    if (_nextLine >= (int)_rawCameraInfo.size.second)
                        done = true;
                }
                if (done) break;
            }
            if (!display->isOpen() || display->shouldExport()) {
                std::lock_guard<std::mutex> lock(_renderMutex);
                _nextLine = (int)_rawCameraInfo.size.second;
            }
            renderThread.join();
            while (display->isOpen() && !display->shouldExport()) {
                display->refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
        } else {
            renderParallel(nullptr);
        }
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
        buildPointLight();
        buildDirectionalLight();
        buildAmbientLight();

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
            auto newPrimitive = _objectFactory.createPrimitive(shapeData.type, shapeData);
            if (newPrimitive) {
                newPrimitive->material = _materialFactory.createMaterial(shapeData.material);
                physical_primitives.push_back(newPrimitive);
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
                newPlane->material = _materialFactory.createMaterialWithParams(planeData.material, planeData.materialParams);
                physical_primitives.push_back(newPlane);
            }
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Planes instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildPointLight()
{
    try {
        for (const auto& [id, pos] : _rawLights.listPoints) {
            Raytracer::Light data;
            data.position = pos;
            data.intensity = Raytracer::RED;
            
            auto newLight = _objectFactory.createLight("Point", data);
            if (newLight)
                _lights.push_back(newLight);
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Point light(s) instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildDirectionalLight()
{
    try {
        for (const auto&[id, direction] : _rawLights.listDirectional) {
            Raytracer::Light data;
            data.direction = direction;
            data.intensity = Raytracer::RED;

            auto newLight = _objectFactory.createLight("Directional", data);
            if (newLight)
                _lights.push_back(newLight);
        }
    } catch (const std::exception& e) {
        throw ErrorException(std::string("Directional light(s) instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::buildAmbientLight()
{
    auto ambientParam = _rawLights.lightParams.find(Raytracer::lightsType::ambient);

    try {
        if (ambientParam != _rawLights.lightParams.end()) {
            Raytracer::Light data;
            data.ambientIntensity = static_cast<float>(ambientParam->second);

            auto newLight = _objectFactory.createLight("Ambient", data);
            if (newLight)
                _lights.push_back(newLight);
        }
    } catch (std::exception& e) {
        throw ErrorException(std::string("Ambient light instantiation failed: ") + e.what());
    }
}

void Raytracer::SceneLoader::renderParallel(Raytracer::SfmlDisplay* display)
{
    try {
        _nextLine = 0;
        unsigned int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) num_threads = 1;
        
        std::vector<std::thread> threads;
        auto startTime = std::chrono::steady_clock::now();
        bool finished = false;

        std::thread monitor(&Raytracer::Progress::monitor, startTime, std::ref(_nextLine), (int)_rawCameraInfo.size.second, std::ref(finished), std::ref(_renderMutex));

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
                    renderLine(j, display);
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
        {
            std::lock_guard<std::mutex> lock(_renderMutex);
            finished = true;
        }
        monitor.join();
    } catch (const std::exception& e) {
        throw CrashException(std::string("Parallel rendering crashed: ") + e.what());
    }
}

Math::Vector3D Raytracer::SceneLoader::computeRayColor(double u, double v)
{
    Raytracer::Ray r = _camera.ray(u, v);
    HitRecord rec;
    
    if (_bvh.intersect(r, 0.001f, 1e9f, rec)) {
        rec.ray = r;
        if (rec.material && !_lights.empty()) {
            Math::Vector3D color = rec.material->getDiffuseColor(rec, _lights, _bvh);
            return Math::Vector3D(color.X / 255.0, color.Y / 255.0, color.Z / 255.0);
        } else {
            return Math::Vector3D(rec.color.X / 255.0, rec.color.Y / 255.0, rec.color.Z / 255.0);
        }
    }
    return Math::Vector3D(0, 0, 0);
}

void Raytracer::SceneLoader::renderLine(int j, Raytracer::SfmlDisplay* display)
{
    try {
        int width = (int)_rawCameraInfo.size.first;
        int height = (int)_rawCameraInfo.size.second;

        for (int i = 0; i < width; i++) {
            Math::Vector3D pixel_color = Antialazing::resolvePixel(
                i, j, width, height, _aaLevel, _aaThreshold,
                [this](double u, double v) { 
                    return computeRayColor(u, v); 
                }
            );

            _pixels[j][i] = pixel_color;
            if (display) {
                display->updatePixel(i, j, pixel_color);
            }
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
