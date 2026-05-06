/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ReflectionMaterial
*/

#include <memory>
#include <algorithm>
#include <cmath>
#include "plugins/Materials/ReflectionMaterial.hpp"
#include "plugins/lights/PointLight.hpp"
#include "spacePartitionning/BVH.hpp"
#include "utils/Ray.hpp"

Raytracer::ReflectionMaterial::ReflectionMaterial(double reflectivity) : _reflectivity(reflectivity) {}

Math::Vector3D Raytracer::ReflectionMaterial::getDiffuseColor(
    const HitRecord& record, 
    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
    const Raytracer::BVH& bvh
) const {
    Math::Vector3D illumination_color(record.color.X * 0.1, record.color.Y * 0.1, record.color.Z * 0.1);
    Math::Vector3D hit_point_vec(record.point.X, record.point.Y, record.point.Z);

    for (auto& light : physical_lights) {
        Math::Vector3D dir_to_light = light->getDirectionToLight(hit_point_vec);
        float dist_to_light = light->getDistanceToLight(hit_point_vec);
        Math::Point3D shadow_origin(
            record.point.X + record.normal.X * 0.001, 
            record.point.Y + record.normal.Y * 0.001, 
            record.point.Z + record.normal.Z * 0.001
        );
        Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);
        HitRecord shadow_rec;
        bool in_shadow = bvh.intersect(shadow_ray, 0.001f, dist_to_light, shadow_rec);
        
        if (!in_shadow) {
            illumination_color = illumination_color + light->calculateIllumination(hit_point_vec, record.normal, record.color);
        }
    }

    Math::Vector3D incoming = record.ray.direction.normalize();
    Math::Vector3D reflected_dir = incoming - (record.normal * (2.0 * incoming.dot(record.normal)));
    reflected_dir = reflected_dir.normalize();
    Math::Point3D reflection_origin(
        record.point.X + record.normal.X * 0.001,
        record.point.Y + record.normal.Y * 0.001,
        record.point.Z + record.normal.Z * 0.001
    );
    Raytracer::Ray reflection_ray(reflection_origin, reflected_dir);
    HitRecord reflection_rec;
    Math::Vector3D reflected_color(0, 0, 0);
    bool hit_reflection = bvh.intersect(reflection_ray, 0.001f, 1e9f, reflection_rec);

    if (hit_reflection && reflection_rec.material != nullptr) {
        reflection_rec.ray = reflection_ray;
        reflected_color = reflection_rec.material->getDiffuseColor(reflection_rec, physical_lights, bvh);
    }
    Math::Vector3D final_color(
        illumination_color.X * (1.0 - _reflectivity) + reflected_color.X * _reflectivity,
        illumination_color.Y * (1.0 - _reflectivity) + reflected_color.Y * _reflectivity,
        illumination_color.Z * (1.0 - _reflectivity) + reflected_color.Z * _reflectivity
    );
    return Math::Vector3D(
        std::min(255.0, std::max(0.0, final_color.X)),
        std::min(255.0, std::max(0.0, final_color.Y)),
        std::min(255.0, std::max(0.0, final_color.Z))
    );
}

extern "C" {
    int getType() { return 2; }
    Raytracer::IMaterial* entryPoint() { return new Raytracer::ReflectionMaterial(0.5); }
    Raytracer::IMaterial* entryPointWithReflectivity(double reflectivity) { return new Raytracer::ReflectionMaterial(reflectivity); }
}
