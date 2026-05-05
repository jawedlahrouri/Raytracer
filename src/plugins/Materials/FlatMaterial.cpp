/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatMaterialFile
*/

#include <memory>
#include <algorithm>
#include "plugins/Materials/FlatMaterial.hpp"
#include "plugins/lights/PointLight.hpp"
#include "spacePartitionning/BVH.hpp"

Raytracer::FlatMaterial::FlatMaterial() {}
Raytracer::FlatMaterial::~FlatMaterial() {}

Math::Vector3D Raytracer::FlatMaterial::getDiffuseColor(
    const HitRecord& record, 
    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
    const Raytracer::BVH& bvh
) const {

    Math::Vector3D illumination_color(
        record.color.X * 0.1,
        record.color.Y * 0.1,
        record.color.Z * 0.1
    );

    for (auto& light : physical_lights) {
        Math::Vector3D hit_point_vec(record.point.X, record.point.Y, record.point.Z);
        Math::Vector3D dir_to_light = light->getDirectionToLight(hit_point_vec);
        double dist_to_light = light->getDistanceToLight(hit_point_vec);

        Math::Point3D shadow_origin(
            record.point.X + record.normal.X * 0.001,
            record.point.Y + record.normal.Y * 0.001,
            record.point.Z + record.normal.Z * 0.001
        );
        Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);

        HitRecord shadow_rec;
        bool in_shadow = bvh.intersect(shadow_ray, 0.001, dist_to_light, shadow_rec);

        if (!in_shadow)
            illumination_color = illumination_color + light->calculateIllumination(hit_point_vec, record.normal, record.color);
    }

    return Math::Vector3D(
        std::min(255.0, illumination_color.X),
        std::min(255.0, illumination_color.Y),
        std::min(255.0, illumination_color.Z)
    );
}

extern "C" {
    int getType() {
        return 2;
    }

    Raytracer::IMaterial* entryPoint() {
        return new Raytracer::FlatMaterial();
    }
}
