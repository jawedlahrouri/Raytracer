#include "plugins/Materials/TransparentMaterial.hpp"
#include "plugins/lights/PointLight.hpp"
#include "spacePartitionning/BVH.hpp"
#include "utils/Ray.hpp"
#include <algorithm>

Raytracer::TransparentMaterial::TransparentMaterial(double opacity) : _opacity(opacity) {}

Math::Vector3D Raytracer::TransparentMaterial::getDiffuseColor(
    const HitRecord& record, 
    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
    const Raytracer::BVH& bvh
) const {
    Math::Vector3D object_color(0, 0, 0);
    Math::Vector3D hit_point_vec(record.point.X, record.point.Y, record.point.Z);

    for (auto& light : physical_lights) {
        Math::Vector3D dir_to_light = light->getDirectionToLight(hit_point_vec);
        float dist_to_light = light->getDistanceToLight(hit_point_vec);
        
        if (!light->canLightBeBlocked()) {
            object_color = object_color + light->calculateIllumination(hit_point_vec, record.normal, record.color);
            continue;
        }
        Math::Point3D shadow_origin(
            record.point.X + record.normal.X * 0.001, 
            record.point.Y + record.normal.Y * 0.001, 
            record.point.Z + record.normal.Z * 0.001
        );
        Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);
        HitRecord shadow_rec;

        bool in_shadow = bvh.intersect(shadow_ray, 0.001f, dist_to_light, shadow_rec);

        if (!in_shadow) {
            object_color = object_color + light->calculateIllumination(hit_point_vec, record.normal, record.color);
        }
    }
    
    Math::Point3D transparent_origin(
        record.point.X + (record.ray.direction.X * 0.001),
        record.point.Y + (record.ray.direction.Y * 0.001),
        record.point.Z + (record.ray.direction.Z * 0.001)
    );
    Raytracer::Ray transparent_ray(transparent_origin, record.ray.direction);
    
    HitRecord bg_rec;
    bool hit_bg = bvh.intersect(transparent_ray, 0.001f, 1e9f, bg_rec);
    Math::Vector3D background_color(0, 0, 0);

    if (hit_bg) {
        bg_rec.ray = transparent_ray;
        if (bg_rec.material != nullptr) {
            background_color = bg_rec.material->getDiffuseColor(bg_rec, physical_lights, bvh);
        } else {
            background_color = bg_rec.color;
        }
    }
    
    Math::Vector3D final_color(
        (object_color.X * _opacity) + (background_color.X * (1.0 - _opacity)),
        (object_color.Y * _opacity) + (background_color.Y * (1.0 - _opacity)),
        (object_color.Z * _opacity) + (background_color.Z * (1.0 - _opacity))
    );

    return Math::Vector3D(
        std::min(255.0, std::max(0.0, final_color.X)),
        std::min(255.0, std::max(0.0, final_color.Y)),
        std::min(255.0, std::max(0.0, final_color.Z))
    );
}

extern "C" {
    int getType() {
        return 2;
    }

    Raytracer::IMaterial* entryPoint(const std::map<std::string, double>& params) {
        double opacity = 0.5;
        if (params.find("opacity") != params.end())
            opacity = params.at("opacity");
        return new Raytracer::TransparentMaterial(opacity);
    }
}
