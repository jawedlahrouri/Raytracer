/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatMaterialFile
*/

#include <memory>
#include "plugins/Materials/FlatMaterial.hpp"
#include "plugins/lights/PointLight.hpp"

Raytracer::FlatMaterial::FlatMaterial()
{
}

Raytracer::FlatMaterial::~FlatMaterial()
{
}

Math::Vector3D Raytracer::FlatMaterial::getDiffuseColor(
    const HitRecord& record, 
    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
    const std::vector<std::shared_ptr<Raytracer::IPrimitive>>& physical_primitives
) const {
    Math::Vector3D illumination_color(15, 15, 15);

    for (auto& light : physical_lights) {
        Math::Vector3D dir_to_light = light->getDirectionToLight(record.point);
        float dist_to_light = light->getDistanceToLight(record.point);
        Math::Point3D shadow_origin(record.point.X + record.normal.X * 0.001, record.point.Y + record.normal.Y * 0.001, record.point.Z + record.normal.Z * 0.001);
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
        if (!in_shadow)
            illumination_color = illumination_color + light->calculateIllumination(record.point, record.normal, record.color);
    }
    
    return illumination_color;
}

extern "C" {
    int getType() {
        return 2;
    }

    IMaterial* entryPoint() {
        return new Raytracer::FlatMaterial();
    }
}
