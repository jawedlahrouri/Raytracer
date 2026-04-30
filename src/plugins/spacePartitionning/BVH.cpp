/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** BVH functions for space partitionning optimisation
*/

#include "../spacePartitionning/BVH.hpp"

void Raytracer::BVH::build(std::vector<std::shared_ptr<IPrimitive>> primitives)
{
    prims = std::move(primitives);
    root = buildRecursive(0, (int)prims.size());
}

bool Raytracer::BVH::intersect(const Ray& ray, double tMin, double tMax, HitRecord& rec) const
{
    return traverseNode(root.get(), ray, tMin, tMax, rec);
}

std::unique_ptr<Raytracer::BVHNode> Raytracer::BVH::buildRecursive(int start, int end)
{
    auto node = std::make_unique<Raytracer::BVHNode>();

    node->bounds = prims[start]->bounds();
    for (int i = start + 1; i < end; ++i)
        node->bounds = AABB::merge(node->bounds, prims[i]->bounds());
    
    int count = end - start;

    if (count <= 4) {
        node->primStart = start;
        node->primCount = count;
        return node;
    }

    int   bestAxis  = 0;
    int   bestSplit = start + count / 2;
    float bestCost  = std::numeric_limits<float>::max();
    float parentSA  = node->bounds.surfaceArea();

    for (int axis = 0; axis < 3; ++axis) {
        std::sort(prims.begin()+start, prims.begin()+end,
            [axis](const auto& a, const auto& b){
                return (&a->centroid().x)[axis] < (&b->centroid().x)[axis];
            });

        for (int split = start+1; split < end; ++split) {
            AABB leftBox  = prims[start]->bounds();
            AABB rightBox = prims[split]->bounds();
            for (int i = start+1; i < split; ++i)
                leftBox  = AABB::merge(leftBox,  prims[i]->bounds());
            for (int i = split+1; i < end;   ++i)
                rightBox = AABB::merge(rightBox, prims[i]->bounds());

            // Coût SAH = SA(L)*N(L) + SA(R)*N(R) / SA(parent)
            float cost = (leftBox.surfaceArea()  * (split - start) +
                        rightBox.surfaceArea() * (end - split))
                        / parentSA;

            if (cost < bestCost) {
                bestCost  = cost;
                bestAxis  = axis;
                bestSplit = split;
            }
        }
    }

    std::sort(prims.begin()+start, prims.begin()+end,
        [bestAxis](const auto& a, const auto& b){
            return (&a->centroid().x)[bestAxis] < (&b->centroid().x)[bestAxis];
        });

    node->left  = buildRecursive(start, bestSplit);
    node->right = buildRecursive(bestSplit, end);
    return node;
}

bool Raytracer::BVH::traverseNode(const Raytracer::BVHNode* node, const Raytracer::Ray& ray, double tMin, double tMax, HitRecord& rec) const
{
    if (!node->bounds.intersect(ray, tMin, tMax))
        return false;

    if (node->isLeaf()) {
        bool hit = false;
        for (int i = node->primStart; i < node->primStart + node->primCount; ++i) {
            HitRecord tmp;
            if (prims[i]->intersect(ray, tMin, tMax, tmp)) {
                tMax = tmp.t;
                rec  = tmp;
                hit  = true;
            }
        }
        return hit;
    }

    HitRecord lRec, rRec;
    bool hitL = traverseNode(node->left.get(),  ray, tMin, tMax, lRec);
    bool hitR = traverseNode(node->right.get(), ray, tMin, tMax, rRec);

    if (hitL && hitR) { rec = (lRec.t < rRec.t) ? lRec : rRec; return true; }
    if (hitL) { rec = lRec; return true; }
    if (hitR) { rec = rRec; return true; }
    return false;
}