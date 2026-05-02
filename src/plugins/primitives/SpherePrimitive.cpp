/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** sphere
*/

#include "./primitives/SpherePrimitive.hpp"
#include <cmath>
#include "./spacePartitionning/AABB.hpp"

bool Raytracer::SpherePrimitive::intersect(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
    Math::Vector3D oc = ray.origin - center;

    float a = ray.direction.dot(ray.direction);
    float b = 2.f * oc.dot(ray.direction);
    float c = oc.dot(oc) - (float)(radius * radius);
    float discriminant = b * b - 4.f * a * c;

    if (discriminant < 0)
        return false;

    float sqrtD = std::sqrt(discriminant);


    float t = (-b - sqrtD) / (2.f * a);
    if (t < tMin || t > tMax) {
        t = (-b + sqrtD) / (2.f * a);
        if (t < tMin || t > tMax)
        return false;
    }

    rec.t      = t;
    rec.point  = ray.at(t); // Point3D du hit
    rec.normal = (rec.point - center) * (1.f / (float)radius); // normale unitaire
    // std::cout << "val red for sphere : " << color.X << std::endl;
    rec.color  = color; // ta couleur à la place de materialID

    return true;
}

Raytracer::AABB Raytracer::SpherePrimitive::bounds() const
{
    AABB box;
    box.min = Math::Vector3D(center.X - radius, center.Y - radius, center.Z - radius);
    box.max = Math::Vector3D(center.X + radius, center.Y + radius, center.Z + radius);
    return box;
}

Math::Point3D Raytracer::SpherePrimitive::centroid() const
{
    return center;
}

void Raytracer::SpherePrimitive::setName(const std::string &name)
{
    _name = name;
}

void Raytracer::SpherePrimitive::setPosition(const Math::Point3D& position)
{
    center = position;    
}


extern "C" {
    int getType() {
        return 0;
    }

    Raytracer::IPrimitive* entryPoint(Raytracer::Shape& data) {
        return new Raytracer::SpherePrimitive(data);
    }
}