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
#include "plugins/lights/PointLight.hpp"
#include "plugins/renderer/Shadow_Ray.hpp"
#include "parsing.hpp"

#include <memory>
#include <limits>

Raytracer::test::test(const Raytracer::Primitive& primitive, const Raytracer::Camera& camera, const Raytracer::Lights& lights) : _primitive(primitive), _camera(camera), _lights(lights), _cam(camera.size.first, camera.size.second, camera.fieldOfView, camera.posCoords, camera.rotaCoords), _pixels(camera.size.second, std::vector<Math::Vector3D>(camera.size.first))
{
}

Raytracer::test::~test()
{
}

void Raytracer::test::createScene()
{
    std::vector<std::shared_ptr<Raytracer::IPrimitive>> physical_primitives;
    std::vector<std::shared_ptr<Raytracer::ILight>> physical_lights;
    Raytracer::ObjectFactory factory; 

    for (const auto& [name, shapeData] : _primitive.listOfShapes) {
        try {
            auto newPrimitive = factory.createPrimitive(shapeData.type, shapeData);
            physical_primitives.push_back(newPrimitive);
        } catch (const ErrorException &e) {
            std::cerr << "Factory Error (" << shapeData.type << "): " << e.what() << std::endl;
        }
    }

    for (const auto& [name, planeData] : _primitive.listOfPlane) {
        try {
            auto newPlane = factory.createPrimitive("Plane", planeData);
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
                }
            }

            if (hit) {
                Math::Vector3D illumination_color(15, 15, 15); 

                for (auto& light : physical_lights) {
                    Math::Vector3D dir_to_light = light->getDirectionToLight(rec.point);
                    float dist_to_light = light->getDistanceToLight(rec.point);

                    Math::Point3D shadow_origin(
                        rec.point.X + rec.normal.X * 0.001,
                        rec.point.Y + rec.normal.Y * 0.001,
                        rec.point.Z + rec.normal.Z * 0.001
                    );
                    Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);
                    
                    bool in_shadow = false;
                    for (auto& primitive_shadow : physical_primitives) {
                        HitRecord shadow_rec;
                        if (primitive_shadow->intersect(shadow_ray, shadow_rec)) {
                            if (shadow_rec.t > 0.001 && shadow_rec.t < dist_to_light) {
                                in_shadow = true;
                                break;
                            }
                        }
                    }
                    if (!in_shadow) {
                        illumination_color = illumination_color + light->calculateIllumination(rec.point, rec.normal, rec.color);
                    }
                }
                pixel_color = illumination_color;
                pixel_color.X = std::min(255.0, pixel_color.X);
                pixel_color.Y = std::min(255.0, pixel_color.Y);
                pixel_color.Z = std::min(255.0, pixel_color.Z);
            }
            _pixels[j][i] = pixel_color;
        }
    }
    Raytracer::PPMExporter exporter;
    exporter.write_image(_camera.size.first, _camera.size.second, _pixels);
    physical_lights.clear();
    physical_primitives.clear();
}