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
#include "RaytracerType.hpp"
#include "utils/HitRecord.hpp"
#include <memory>
#include <limits>
#include "plugins/lights/PointLight.hpp"
#include "plugins/renderer/Shadow_Ray.hpp"

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

            HitRecord rec;
            bool hit = false;
            double closest_so_far = std::numeric_limits<double>::max();

            for (auto& primitive : physical_primitives) {
                HitRecord temp_rec;
                if (primitive->intersect(r, temp_rec) && temp_rec.t < closest_so_far) {
                    hit = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            if (hit) {
                Math::Vector3D illumination_color(0, 0, 0);

                for (auto const& [id, light_pos] : _lights.listPoints) {
                    Raytracer::PointLight light(light_pos, Raytracer::RED);
                    Math::Vector3D dir_to_light = light.getDirectionToLight(rec.point);
                    float dist_to_light = light.getDistanceToLight(rec.point);
                    Math::Point3D shadow_origin(rec.point.X + rec.normal.X * 0.01, rec.point.Y + rec.normal.Y * 0.01, rec.point.Z + rec.normal.Z * 0.01);
                    Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);
                    bool in_shadow = false;
                    
                    for (auto& primitive : physical_primitives) {
                        HitRecord shadow_rec;
                        if (primitive->intersect(shadow_ray, shadow_rec) && shadow_rec.t > 0.01 && shadow_rec.t < dist_to_light) {
                            in_shadow = true;
                            break;
                        }
                    }
                    if (!in_shadow) {
                        illumination_color = illumination_color + light.calculateIllumination(rec.point, rec.normal, rec.color);
                    }
                }
                _pixels[j][i] = illumination_color + (rec.color * 0.2);
        }
    }
    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
    }
}