#ifndef TRANSPARENT_MATERIAL_HPP_
#define TRANSPARENT_MATERIAL_HPP_

#include <memory>
#include <vector>
#include "math/Vector3D.hpp"
#include "interface/IMaterial.hpp"

namespace Raytracer {
    class TransparentMaterial : public IMaterial {
        private:
            double _opacity;
        public:
            TransparentMaterial(double opacity = 0.5);
            ~TransparentMaterial() = default;

            Math::Vector3D getDiffuseColor(
                const HitRecord& record, 
                const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, 
                const Raytracer::BVH& bvh
            ) const override;
    };
}
#endif /* !TRANSPARENT_MATERIAL_HPP_ */
