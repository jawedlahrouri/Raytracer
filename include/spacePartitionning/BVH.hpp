/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** BVH algro space partitionning algo for optimisation
*/

#ifndef BVH_HPP_
#define BVH_HPP_

#include "./../interface/IPrimitive.hpp"
#include "./../math/Vector3D.hpp"
#include "AABB.hpp"

namespace Raytracer {
    struct BVHNode {
        AABB bounds;
        std::unique_ptr<BVHNode> left, right;
        int primStart = -1, primCount = 0;
        
        bool isLeaf() const { return primCount > 0; }
    };
}

namespace Raytracer {
    class BVH {
        private:
            // Construit récursivement le BVH avec critère SAH
            std::unique_ptr<Raytracer::BVHNode> buildRecursive(int start, int end);
        public:
            std::vector<std::shared_ptr<IPrimitive>> prims;
            std::unique_ptr<BVHNode> root;
            
            BVH() = default;
            ~BVH() = default;

            void build(std::vector<std::shared_ptr<IPrimitive>> primitives);
            bool intersect(const Ray& ray, double tMin, double tMax, HitRecord& rec) const;
            bool traverseNode(const BVHNode* node, const Ray& ray, double tMin, double tMax, HitRecord& rec) const;
    };
}

#endif