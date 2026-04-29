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
#include <memory>

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second), _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first))
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::createScene()
{
    std::vector<std::shared_ptr<Raytracer::IPrimitive>> physical_primitives;
    Raytracer::ObjectFactory factory; 

    for (const auto& [name, shapeData] : _primitive.listOfShapes) {
        try {
            auto newPrimitive = factory.createPrimitive("Sphere", name);

            newPrimitive->setPosition(shapeData.coords);

            physical_primitives.push_back(newPrimitive);
        } catch (const ErrorException &e) {
            std::cerr << "Factory Error: " << e.what() << std::endl;
        }
    }

    for (const auto& [name, planeData] : _primitive.listOfPlane) {
        try {
            auto newPlane = factory.createPrimitive("Plane", name);

            newPlane->setPosition(Math::Point3D(0, 0, planeData.positions));
            newPlane->setAxis(planeData.axis);

            physical_primitives.push_back(newPlane);
        } catch (const ErrorException &e) {
            std::cerr << "Factory Error: " << e.what() << std::endl;
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

            for (auto& primitive : physical_primitives) {
                HitRecord temp_rec;
                if (primitive->intersect(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                    pixel_color = Math::Vector3D(255, 0, 0); 
                }
            
            }
            _pixels[j][i] = pixel_color;
        }
    }
    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
}