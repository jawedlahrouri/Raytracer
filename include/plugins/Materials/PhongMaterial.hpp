/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** PhongMaterial
*/

#ifndef PHONG_MATERIAL_HPP_
#define PHONG_MATERIAL_HPP_

#include <memory>
#include "math/Vector3D.hpp"
#include "interface/IMaterial.hpp"
#include "spacePartitionning/BVH.hpp"

namespace Raytracer {
    class PhongMaterial : public IMaterial {
        public:
            PhongMaterial(double shininess = 32.0, double specular = 0.5);
            ~PhongMaterial() = default;
            Math::Vector3D getDiffuseColor(
                const HitRecord& record,
                const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights,
                const Raytracer::BVH& bvh
            ) const override;

        private:
            double _shininess;
            double _specular;
    };
}

#endif /* !PHONG_MATERIAL_HPP_ */
