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

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second), _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first))
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::createScene()
{
    //futurement ce qui vas etre appeller par la factory a chaque sphere rencontrer i guess
    std::vector<Raytracer::SpherePrimitive> physical_sphere;
    for (const auto& [name, shapeData] : _primitive.listOfShapes) {
        if (shapeData.shapeName.rfind("Sphere", 0) == 0) {
            physical_sphere.push_back(Raytracer::SpherePrimitive(shapeData)); // ici il faudras appeler l'entry point via la factory
        }
    }

    std::vector<Raytracer::PlanePrimitive> physical_plane;
    for (const auto& [name, planeData] : _primitive.listOfPlane) {
        physical_plane.push_back(Raytracer::PlanePrimitive(planeData)); 
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
            for (auto& sphere : physical_sphere) {
                HitRecord temp_rec;
                if (sphere.intersect(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                    pixel_color = Math::Vector3D(255, 0, 0);
                }
            }

            for (auto& plane : physical_plane) {
                HitRecord temp_rec;
                
                if (plane.intersect(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                    pixel_color = Math::Vector3D(0, 255, 0);
                }
            }

            _pixels[j][i] = pixel_color;
        }
    }
    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
}
