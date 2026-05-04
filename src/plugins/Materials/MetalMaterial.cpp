/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatMaterialFile
*/

#include <memory>
#include "plugins/Materials/MetalMaterial.hpp"
#include "plugins/lights/PointLight.hpp"

Raytracer::MetalMaterial::MetalMaterial()
{
}

Raytracer::MetalMaterial::~MetalMaterial()
{
}

Math::Vector3D Raytracer::MetalMaterial::getDiffuseColor(
    const HitRecord& record, 
    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
    const std::vector<std::shared_ptr<Raytracer::IPrimitive>>& physical_primitives,
    const Raytracer::Ray& ray
) const {
    Math::Vector3D illumination_color(0, 0, 0);
    Math::Vector3D ray_origin_vec(ray.origin.X, ray.origin.Y, ray.origin.Z);
    Math::Vector3D view_dir = (ray_origin_vec - record.point).normalize();
    double shininess = 0.8;
    double specular_strength = 0.8;

    for (auto& light : physical_lights) {
        Math::Vector3D dir_to_light = light->getDirectionToLight(record.point);
        float dist_to_light = light->getDistanceToLight(record.point);        
        Math::Vector3D shadow_origin_vec = record.point + record.normal * 0.001;
        Math::Point3D shadow_origin(shadow_origin_vec.X, shadow_origin_vec.Y, shadow_origin_vec.Z);
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
            Math::Vector3D diffuse = light->calculateIllumination(record.point, record.normal, record.color) * 0.2;
            Math::Vector3D halfway_dir = (dir_to_light + view_dir).normalize();
            double spec = std::pow(std::max(0.0, record.normal.dot(halfway_dir)), shininess);
            Math::Vector3D specular = Math::Vector3D(255, 255, 255) * spec * specular_strength;
            
            illumination_color = illumination_color + diffuse + specular;
        }
    }
    
    return illumination_color;
}

extern "C" {
    int getType() {
        return 2;
    }

    IMaterial* entryPoint() {
        return new Raytracer::MetalMaterial();
    }
}