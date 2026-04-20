/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Object Factory
*/
#include "ObjectFactory.hpp"
#include "FactoryException.hpp"

Raytracer::ObjectFactory::ObjectFactory()
{
    // Primitives Objects
    // _createPrimitive["sphere"] = []() { return std::make_unique<Raytracer::SphereObject(); };

    // Lights Objects
    // _createLight["flashy"] = []() { return std::make_unique<Raytracer::FlashyObject(); };
}

std::unique_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type)
{
    if (_createPrimitive.find(type) == _createPrimitive.end) {
        throw Raytracer::FactoryException("Unknow primitive type :" + type);
    }

    return _createPrimitive[type]();
}

std::unique_ptr<Raytracer::ILight> Raytracer::ObjectFactory::createLight(const std::string &type)
{
    if (_createLight.find(type) == _createLight.end()) {
        throw Raytracer::FactoryException("Unknow light type :" + type);
    }

    return _createLight[type]();
}
