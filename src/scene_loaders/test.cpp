/*
** EPITECH PROJECT, 2026
** test
** File description:
** test de link le parsing avec le bootstrap
*/

#include "config/test.hpp"
#include "utils/Ray.hpp"
#include "plugins/renderer/ppm_export.hpp"
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
    //futurement ce qui vas etre appeller par la factory a chaque sphere rencontrer i guess
    std::vector<std::unique_ptr<Raytracer::IPrimitive>> shapes;
    for (const auto& [name, shapeData] : _primitive.listOfShapes) {
        if (shapeData.shapeName.rfind("Sphere", 0) == 0) {
            shapes.push_back(std::make_unique<Raytracer::SpherePrimitive>(shapeData)); // ici il faudras appeler l'entry point via la factory
        }
    }

    for (const auto& [name, planeData] : _primitive.listOfPlane) {
        shapes.push_back(std::make_unique<Raytracer::PlanePrimitive>(planeData)); 
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
            for (std::size_t i = 0; i <= shapes.size(); i++) {
                HitRecord temp_rec;
                if (shapes.at(i)->intersect(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                    // pixel_color = ; a coder mais jsp comment
                }
            
            }
            _pixels[j][i] = pixel_color;
        }
    }
    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
}
