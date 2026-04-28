/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Object Factory
*/

#include "design_pattern/ObjectFactory.hpp"

Raytracer::ObjectFactory::ObjectFactory()
{
    // Primitives Objects
    // _createPrimitive["Sphere"] = []() { return std::make_shared<Raytracer::Sphere(); };
    // _createPrimitive["Plane"] = []() { return std::make_shared<Raytracer::Plane(); };

    // Lights Objects
    // _createLight["ambient"] = []() { return std::make_shared<Raytracer::Ambient(); };
    // _createLight["directional"] = []() { return std::make_shared<Raytracer::Directional(); };
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type)
{
    int id = 0;

    if (_createPrimitive.find(type) == _createPrimitive.end()) {
        throw ErrorException("Unknow primitive type :" + type);
    }

    id = _counts[type]++;   
    std::string primitiveOrderedName = type + "_" + std::to_string(id);
    auto newPrimitive = _createPrimitive[type]();
    // newPrimitive->setName(primitiveOrderedName);

    return newPrimitive;
}

std::shared_ptr<Raytracer::ILight> Raytracer::ObjectFactory::createLight(const std::string &type)
{
    int id = 0;

    if (_createLight.find(type) == _createLight.end()) {
        throw ErrorException("Unknow light type :" + type);
    }

    id = _counts[type]++;
    std::string lightOrderedName = type + "_" + std::to_string(id);
    auto newLight = _createLight[type]();
    // newLight->setName(lightOrderedName);

    return newLight;
}
