/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Object Factory
*/

#include "design_pattern/ObjectFactory.hpp"

std::shared_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type, const Raytracer::Shape &data)
{
    std::string path = "./plugins/lib" + type + "Primitive.so";

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::IPrimitive>>(path);

        Raytracer::IPrimitive* instance = loader->getInstance("entryPoint", data);
        if (!instance) {
            throw ErrorException("EntryPoint returned nullptr for " + type);
        }
        std::shared_ptr<Raytracer::IPrimitive> newPrimitive(instance);
        _primitiveLoader.push_back(std::move(loader));

        return newPrimitive;
    } catch (const std::exception &e) {
        throw ErrorException("Factory Error (" + type + "): " + e.what());
    }
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type, const Raytracer::Plane &data)
{
    std::string path = "./plugins/lib" + type + "Primitive.so";
    try {
        auto loader = std::make_unique<DLLoader<Raytracer::IPrimitive>>(path);

        Raytracer::IPrimitive* instance = loader->getInstance("entryPoint", data);
        if (!instance) {
            throw ErrorException("EntryPoint returned nullptr for Plane");
        }
        std::shared_ptr<Raytracer::IPrimitive> newPrimitive(instance);
        _primitiveLoader.push_back(std::move(loader));
        
        return newPrimitive;
    } catch (const std::exception &e) {
        throw ErrorException("Factory Error (Plane): " + std::string(e.what()));
    }
}

std::shared_ptr<Raytracer::ILight> Raytracer::ObjectFactory::createLight(const std::string &type)
{
    std::string path = "./plugins/lib" + type + "Light.so";

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::ILight>>(path);
        Raytracer::ILight* getEntryPoint = loader->getInstance("entryPoint");

        if (!getEntryPoint) {
            throw ErrorException("EntryPoint returned nullptr for " + type);
        }
        std::shared_ptr<Raytracer::ILight> newLight(getEntryPoint);
        _lightLoader.push_back(std::move(loader));

        return newLight;
    } catch (const std::exception &e) {
        throw ErrorException("Failed to load plugin " + type + ":" + e.what());
    }
}
