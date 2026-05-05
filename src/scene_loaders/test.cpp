/*
** EPITECH PROJECT, 2026
** test
** File description:
** test de link le parsing avec le bootstrap
*/

#include "config/test.hpp"
#include "utils/Ray.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "design_pattern/ObjectFactory.hpp"
#include "primitives/SpherePrimitive.hpp"
#include "primitives/PlanePrimitive.hpp"
#include "spacePartitionning/BVH.hpp"
#include "RaytracerType.hpp"
#include "utils/HitRecord.hpp"
#include "plugins/lights/PointLight.hpp"
#include "plugins/renderer/Shadow_Ray.hpp"
#include "parsing.hpp"
#include "plugins/Materials/FlatMaterial.hpp"
#include "design_pattern/MaterialFactory.hpp"
#include "display/sfml_display.hpp"
#include <memory>
#include <limits>
#include <thread>
#include <mutex>

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second, camera.fieldOfView, camera.posCoords, camera.rotaCoords), _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first))
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::createScene(BVH& bvh, Raytracer::ObjectFactory& factory, SfmlDisplay* display)
{
    std::vector<std::shared_ptr<Raytracer::IPrimitive>> physical_primitives;
    Raytracer::MaterialFactory material_factory;
    std::vector<std::shared_ptr<Raytracer::ILight>> physical_lights;

    for (const auto& [name, shapeData] : _primitive.listOfShapes) {
        try {
            auto prim = factory.createPrimitive(shapeData.type, shapeData);
            auto material = material_factory.createMaterial(shapeData.material);
            prim->material = material;
            physical_primitives.push_back(prim);
        } catch (const ErrorException& e) {
            std::cerr << "Factory Error: " << e.what() << std::endl;
        }
    }

    for (const auto& [name, planeData] : _primitive.listOfPlane) {
        try {
            auto newPlane = factory.createPrimitive("Plane", planeData);   
            auto material = material_factory.createMaterial(planeData.material);
            newPlane->material = material;
            physical_primitives.push_back(newPlane);
        } catch (const ErrorException &e) {
            std::cerr << "Factory Error (Plane): " << e.what() << std::endl;
        }
    }

    for (const auto& [id, pos] : _lights.listPoints) {
        try {
            Raytracer::Light data;
            data.position = pos;
            data.intensity = Raytracer::RED;
            
            auto newLight = factory.createLight("Point", data);
            if (newLight) physical_lights.push_back(newLight);
        } catch (const std::exception &e) {
            std::cerr << "Factory Error (PointLight " << id << "): " << e.what() << std::endl;
        }
    }
    bvh.build(std::move(physical_primitives));
    // Lignes de debug
    std::cerr << "BVH prims count: " << bvh.getPrimCount() << std::endl;

    for (int j = 0; j < _camera.size.second; j++) {
        for (int i = 0; i < _camera.size.first; i++) {
            double u = static_cast<double>(i) / (_camera.size.first - 1);
            double v = static_cast<double>(j) / (_camera.size.second - 1);
            Raytracer::Ray r = _cam.ray(u, v);

            Math::Vector3D pixel_color(0, 0, 0);
            HitRecord rec;
            if (bvh.intersect(r, 0.001f, 1e9f, rec)) {
                if (rec.material && !physical_lights.empty()) {
                    Math::Vector3D lit = rec.material->getDiffuseColor(rec, physical_lights, bvh);
                    pixel_color = Math::Vector3D(
                        lit.X / 255.0,
                        lit.Y / 255.0,
                        lit.Z / 255.0
                    );
                } else {
                    pixel_color = Math::Vector3D(
                        rec.color.X / 255.0,
                        rec.color.Y / 255.0,
                        rec.color.Z / 255.0
                    );
                }
            }
            // Clamp colors to [0, 1] to avoid crash in PPMExporter
            pixel_color.X = std::max(0.0, std::min(1.0, pixel_color.X));
            pixel_color.Y = std::max(0.0, std::min(1.0, pixel_color.Y));
            pixel_color.Z = std::max(0.0, std::min(1.0, pixel_color.Z));
            
            _pixels[j][i] = pixel_color;
            
            if (display) {
                display->updatePixel(i, j, pixel_color);
            }
        }
        if (display) {
            display->refresh();
            if (!display->isOpen())
                return;
            if (display->shouldExport())
                break;
        }
    }
    ThreadScene(bvh, physical_lights);

    // lignes de debug 
    int hitCount = 0;
    for (int j = 0; j < _camera.size.second; j++)
        for (int i = 0; i < _camera.size.first; i++)
            if (_pixels[j][i].X != 0 || _pixels[j][i].Y != 0 || _pixels[j][i].Z != 0)
                hitCount++;
    std::cerr << "Pixels hit: " << hitCount << "/" 
            << _camera.size.first * _camera.size.second << std::endl;

    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
    physical_lights.clear();
    physical_primitives.clear();
}