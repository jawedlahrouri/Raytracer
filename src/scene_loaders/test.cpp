/*
** EPITECH PROJECT, 2026
** test
** File description:
** test de link le parsing avec le bootstrap
*/

#include "config/test.hpp"
#include "utils/Ray.hpp"
#include "plugins/renderer/ppm_export.hpp"
#include "RaytracerType.hpp"
#include "utils/HitRecord.hpp"
#include <memory>
#include <limits>

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second), _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first))
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::createScene()
{
    //futurement ce qui vas etre appeller par la factory a chaque sphere rencontrer i guess
    std::vector<std::unique_ptr<Raytracer::IPrimitive>> shapes;
    for (auto& [name, shapeData] : _primitive.listOfShapes) {
        if (shapeData.shapeName.rfind("Sphere", 0) == 0) {
            try {
                auto loader = std::make_unique<DLLoader<Raytracer::IPrimitive>>("./plugins/libSpherePrimitive.so");
                auto ptr = loader->getInstance("entryPoint", shapeData);
                if (!ptr) {
                    std::cerr << "Erreur: entryPoint a retourné nullptr pour SpherePrimitive" << std::endl;
                }
                shapes.push_back(std::unique_ptr<Raytracer::IPrimitive>(ptr));
                _loaders.push_back(std::move(loader));
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors du chargement dynamique de SpherePrimitive: " << e.what() << std::endl;
            }
        }
    }

    for (auto& [name, planeData] : _primitive.listOfPlane) {
        try {
            auto loader = std::make_unique<DLLoader<Raytracer::IPrimitive>>("./plugins/libPlanesPrimitive.so");
            auto ptr = loader->getInstance("entryPoint", planeData);
            if (!ptr) {
                std::cerr << "Erreur: entryPoint a retourné nullptr pour PlanePrimitive" << std::endl;
            }
            shapes.push_back(std::unique_ptr<Raytracer::IPrimitive>(ptr));
            _loaders.push_back(std::move(loader));
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors du chargement dynamique de PlanePrimitive: " << e.what() << std::endl;
        }
    }

    for (int j = 0; j < _camera.size.second; j++) {
        for (int i = 0; i < _camera.size.first; i++) {
            double u = static_cast<double>(i) / (_camera.size.first - 1);
            double v = static_cast<double>(j) / (_camera.size.second - 1);
            Raytracer::Ray r = _cam.ray(u, v);

            Math::Vector3D pixel_color(0, 0, 0);

            HitRecord rec;
            bool hit = false;
            double closest_so_far = std::numeric_limits<double>::max();
            for (std::size_t k = 0; k < shapes.size(); k++) {
                HitRecord temp_rec;
                if (shapes[k]->intersect(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            if (hit) {
                pixel_color = rec.color;
            }
            _pixels[j][i] = pixel_color;
        }
    }
    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
}
