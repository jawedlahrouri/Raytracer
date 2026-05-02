/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** FLATMaterial
*/

#ifndef FLAT_MATERIAL_HPP_
    #define FLAT_MATERIAL_HPP_
    #include <memory>
    #include "math/Vector3D.hpp"
    #include "interface/IMaterial.hpp"

namespace Raytracer {
    class FlatMaterial : public IMaterial {
        public:
            FlatMaterial();
            ~FlatMaterial();
            Math::Vector3D getDiffuseColor(const HitRecord& record, const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, const std::vector<std::shared_ptr<Raytracer::IPrimitive>>& physical_primitives) const override;
    };
}

#endif /* !FLAT_MATERIAL_HPP_ */
