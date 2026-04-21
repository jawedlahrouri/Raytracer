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
    // _createPrimitive["sphere"] = [](const myjson::JsonValue &config) { return std::make_unique<Raytracer::SphereObject(config); };
    // _createPrimitive["plane"] = [](const myjson::JsonValue &config) { return std::make_unique<Raytracer::PlaneObject(config); };

    // Lights Objects
    // _createLight["ambient"] = [](const myjson::JsonValue &config) { return std::make_unique<Raytracer::AmbientObject(config); };
    // _createLight["directional"] = [](const myjson::JsonValue &config) { return std::make_unique<Raytracer::DirectionalObject(config); };
}

std::unique_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type, const myjson::JsonValue &config)
{
    if (_createPrimitive.find(type) == _createPrimitive.end) {
        throw Raytracer::FactoryException("Unknow primitive type :" + type);
    }

    return _createPrimitive[type](config);
}

std::unique_ptr<Raytracer::ILight> Raytracer::ObjectFactory::createLight(const std::string &type, const myjson::JsonValue &config)
{
    if (_createLight.find(type) == _createLight.end()) {
        throw Raytracer::FactoryException("Unknow light type :" + type);
    }

    return _createLight[type](config);
}
