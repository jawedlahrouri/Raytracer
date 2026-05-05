/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include <memory>
#include "utils/Ray.hpp"
#include "utils/HitRecord.hpp"
#include "interface/ILight.hpp"
#include "interface/IPrimitive.hpp"
#include "math/Vector3D.hpp"
#include "RaytracerType.hpp"
#include "parsing.hpp"
#include "spacePartitionning/BVH.hpp"

namespace Raytracer {
    class IMaterial {
        public:
            IMaterial() = default;
            virtual ~IMaterial() = default;
    
        virtual Math::Vector3D getDiffuseColor(const HitRecord& record, const std::vector<std::shared_ptr<Raytracer::ILight>>& physical_lights, const Raytracer::BVH& bvh) const = 0;
        protected:
        private:
    };
}

#endif /* !IMATERIAL_HPP_ */
