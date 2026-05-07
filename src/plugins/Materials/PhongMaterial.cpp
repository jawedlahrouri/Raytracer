/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PhongMaterial
*/

#include <memory>
#include <algorithm>
#include <cmath>
#include "plugins/Materials/PhongMaterial.hpp"
#include "plugins/lights/PointLight.hpp"
#include "spacePartitionning/BVH.hpp"

Raytracer::PhongMaterial::PhongMaterial(double shininess, double specular) : _shininess(shininess), _specular(specular)
{
}

Math::Vector3D Raytracer::PhongMaterial::getDiffuseColor(const HitRecord& record, const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, const Raytracer::BVH& bvh) const
{
    Math::Vector3D final_color(0, 0, 0);
    Math::Vector3D hit_point_vec(record.point.X, record.point.Y, record.point.Z);
    Math::Vector3D V = record.ray.direction * -1.0;
    double v_len = V.length();

    if (v_len > 0)
        V = V / v_len;
    for (auto& light : physical_lights) {
        Math::Vector3D dir_to_light = light->getDirectionToLight(hit_point_vec);
        double dist_to_light = light->getDistanceToLight(hit_point_vec);

        bool in_shadow = false;
        if (light->canLightBeBlocked()) {
            Math::Point3D shadow_origin(
                record.point.X + record.normal.X * 0.001,
                record.point.Y + record.normal.Y * 0.001,
                record.point.Z + record.normal.Z * 0.001
            );
            Raytracer::Ray shadow_ray(shadow_origin, dir_to_light);

            HitRecord shadow_rec;
            in_shadow = bvh.intersect(shadow_ray, 0.001, dist_to_light, shadow_rec);
        }

        if (!in_shadow) {
            Math::Vector3D light_contrib = light->calculateIllumination(hit_point_vec, record.normal, record.color);
            final_color = final_color + light_contrib;
            double l_len = dir_to_light.length();
        
            if (l_len > 0) {
                Math::Vector3D L = dir_to_light;
                Math::Vector3D N = record.normal;
                
                double n_dot_l = N.dot(L);
                if (n_dot_l > 0.0) {
                    Math::Vector3D R = N * (2.0 * n_dot_l) - L;
                    double r_len = R.length();
                    if (r_len > 0) R = R / r_len;

                    double v_dot_r = V.dot(R);
                    if (v_dot_r > 0.0) {
                        double spec_factor = std::pow(v_dot_r, _shininess);
                        double spec_contrib = spec_factor * _specular * 255.0; 
                        final_color = final_color + Math::Vector3D(spec_contrib, spec_contrib, spec_contrib);
                    }
                }
            }
        }
    }

    return Math::Vector3D(
        std::min(255.0, final_color.X),
        std::min(255.0, final_color.Y),
        std::min(255.0, final_color.Z)
    );
}

extern "C" {
    int getType() {
        return 2;
    }

    Raytracer::IMaterial* entryPoint() {
        return new Raytracer::PhongMaterial();
    }

    Raytracer::IMaterial* entryPointWithPhong(double shininess, double specular) {
        return new Raytracer::PhongMaterial(shininess, specular);
    }
}
