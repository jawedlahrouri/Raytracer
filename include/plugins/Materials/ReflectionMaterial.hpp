/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Reflection
*/

#ifndef REFLECTION_MATERIAL_HPP_
    #define REFLECTION_MATERIAL_HPP_

    #include <memory>
    #include <vector>
    #include "math/Vector3D.hpp"
    #include "interface/IMaterial.hpp"

    namespace Raytracer {
        class ReflectionMaterial : public IMaterial {
            private:
                double _reflectivity;
            public:
                ReflectionMaterial(double reflectivity = 0.5);
                ~ReflectionMaterial() = default;

                Math::Vector3D getDiffuseColor(
                    const HitRecord& record, 
                    const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
                    const Raytracer::BVH& bvh
                ) const override;
        };
    }
#endif /* !REFLECTION_MATERIAL_HPP_ */
