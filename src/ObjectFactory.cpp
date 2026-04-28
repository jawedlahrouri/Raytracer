/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Object Factory
*/
#include "../include/design_pattern/ObjectFactory.hpp"
#include "../include/exception.hpp"

Raytracer::ObjectFactory::ObjectFactory()
{
    // Primitives Objects
    // _createPrimitive["Sphere"] = []() { return std::make_shared<Raytracer::Sphere(); };
    // _createPrimitive["Plane"] = []() { return std::make_shared<Raytracer::Plane(); };

    // Lights Objects
    // _createLight["ambient"] = []() { return std::make_shared<Raytracer::Ambient(); };
    // _createLight["directional"] = []() { return std::make_shared<Raytracer::Directional(); };
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type, const std::string name)
{
    if (_createPrimitive.find(type) == _createPrimitive.end()) {
        throw ErrorException("Unknow primitive type :" + type);
    }
    auto newPrimitive = _createPrimitive[type]();
    newPrimitive->setName(name);

    return newPrimitive;
}

std::shared_ptr<Raytracer::ILight> Raytracer::ObjectFactory::createLight(const std::string &type, const std::string name)
{
    if (_createLight.find(type) == _createLight.end()) {
        throw ErrorException("Unknow light type :" + type);
    }
    auto newLight = _createLight[type]();
    newLight->setName(name);

    return newLight;
}
