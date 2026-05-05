#include <memory>
#include <algorithm>
#include <cmath>
#include "plugins/Materials/MetalMaterial.hpp"
#include "plugins/lights/PointLight.hpp"
#include "spacePartitionning/BVH.hpp"

Raytracer::MetalMaterial::MetalMaterial() {}
Raytracer::MetalMaterial::~MetalMaterial() {}

Math::Vector3D Raytracer::MetalMaterial::getDiffuseColor(
    const HitRecord& record, 
    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
    const Raytracer::BVH& bvh
) const {
    Math::Vector3D illumination_color(0, 0, 0);
    Math::Vector3D ray_origin_vec(record.ray.origin.X, record.ray.origin.Y, record.ray.origin.Z);
    Math::Vector3D hit_point_vec(record.point.X, record.point.Y, record.point.Z);
    Math::Vector3D view_dir = (ray_origin_vec - hit_point_vec).normalize();
    double shininess = 0.8;
    double specular_strength = 0.8;

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
            Math::Vector3D diffuse = light->calculateIllumination(hit_point_vec, record.normal, record.color) * 0.2;
            Math::Vector3D halfway_dir = (dir_to_light + view_dir).normalize();
            double spec = std::pow(std::max(0.0, record.normal.dot(halfway_dir)), shininess);
            Math::Vector3D specular = Math::Vector3D(255, 255, 255) * spec * specular_strength;
            
            illumination_color = illumination_color + diffuse + specular;
        }
    }
    return Math::Vector3D(
        std::min(255.0, std::max(0.0, illumination_color.X)),
        std::min(255.0, std::max(0.0, illumination_color.Y)),
        std::min(255.0, std::max(0.0, illumination_color.Z))
    );
}

extern "C" {
    int getType() { return 2; }
    Raytracer::IMaterial* entryPoint() { return new Raytracer::MetalMaterial(); }
}
