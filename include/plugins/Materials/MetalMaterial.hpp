/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** MetalMaterial
*/

#ifndef METAL_MATERIAL_HPP_
    #define METAL_MATERIAL_HPP_
    #include <memory>
    #include "math/Vector3D.hpp"
    #include "interface/IMaterial.hpp"

namespace Raytracer {
    class MetalMaterial : public IMaterial {
        public:
            MetalMaterial();
            ~MetalMaterial();
            Math::Vector3D getDiffuseColor(
                const HitRecord& record,
                const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights,
                const std::vector<std::shared_ptr<Raytracer::IPrimitive>>& physical_primitives,
                const Raytracer::Ray& ray
            ) const override;
    };
}

#endif /* !METAL_MATERIAL_HPP_ */
