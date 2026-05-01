/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatMaterialFile
*/

#include <memory>
#include "Materials/FlatMaterial.hpp"
#include "plugins/lights/PointLight.hpp"

Raytracer::FlatMaterial::FlatMaterial()
{
}

Raytracer::FlatMaterial::~FlatMaterial()
{
}

Math::Vector3D Raytracer::FlatMaterial::getDiffuseColor(
    const HitRecord& record, 
    const Raytracer::Lights& lights, 
    const std::vector<std::shared_ptr<Raytracer::IPrimitive>>& physical_primitives
) const {
    Math::Vector3D illumination_color(0, 0, 0);

    for (auto const& [id, light_pos] : lights.listPoints) {
        Raytracer::PointLight light(light_pos, Raytracer::RED);
        Math::Vector3D dir_to_light = light.getDirectionToLight(record.point);
        float dist_to_light = light.getDistanceToLight(record.point);
        bool in_shadow = false;
        Math::Point3D shadow_origin(record.point.X + record.normal.X * 0.01, record.point.Y + record.normal.Y * 0.01, record.point.Z + record.normal.Z * 0.01);
        Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);
        for (const auto& primitive_shadow : physical_primitives) {
            HitRecord shadow_rec;
            if (primitive_shadow->intersect(shadow_ray, shadow_rec) && 
                shadow_rec.t > 0.01 && shadow_rec.t < dist_to_light) {
                in_shadow = true;
                break;
            }
        }
        if (!in_shadow)
            illumination_color = illumination_color + light.calculateIllumination(record.point, record.normal, record.color);
    }
    return illumination_color + (record.color * lights.lightParams.at(Raytracer::lightsType::ambient));
}
