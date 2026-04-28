/*
** EPITECH PROJECT, 2026
** test
** File description:
** test de link le parsing avec le bootstrap
*/

#include "config/test.hpp"
#include "objects/Sphere.hpp"
#include "utils/Ray.hpp"
#include "objects/Plane.hpp"
#include "plugins/renderer/ppm_export.hpp"

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second), _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first))
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::createScene()
{
    //futurement ce qui vas etre appeller par la factory a chaque sphere rencontrer i guess
    std::vector<Raytracer::Sphere> physical_sphere;
    for (const auto& [name, shapeData] : _primitive.listOfShapes) {
        if (shapeData.shapeName.rfind("Sphere", 0) == 0) {
            Math::Point3D center(shapeData.coords.at(Raytracer::coordType::x), shapeData.coords.at(Raytracer::coordType::y), shapeData.coords.at(Raytracer::coordType::z));
            double radius = shapeData.specs.at(Raytracer::specsType::r);
            physical_sphere.push_back(Raytracer::Sphere(center, radius));
        }
    }

    std::vector<Raytracer::PlaneClass> physical_plane;
    for (const auto& [name, planeData] : _primitive.listOfPlane) {
        Math::Vector3D normal(planeData.axis.at(Raytracer::planesType::X), planeData.axis.at(Raytracer::planesType::Y), planeData.axis.at(Raytracer::planesType::Z));
        Math::Point3D center(0, 0, planeData.positions);
        physical_plane.push_back(Raytracer::PlaneClass(center, normal));
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
                if (sphere.hits(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                    pixel_color = Math::Vector3D(255, 0, 0);
                }
            }

            for (auto& plane : physical_plane) {
                HitRecord temp_rec;
                
                if (plane.hits(r, temp_rec) && temp_rec.t < closest_so_far) {
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
