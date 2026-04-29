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
    // _createPrimitive["Sphere"] = []() { return std::make_shared<Raytracer::SpherePrimitive(); };
    // _createPrimitive["Plane"] = []() { return std::make_shared<Raytracer::PlanePrimitive(); };

    // Lights Objects
    // _createLight["ambient"] = []() { return std::make_shared<Raytracer::Ambient(); };
    // _createLight["directional"] = []() { return std::make_shared<Raytracer::Directional(); };
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::ObjectFactory::createPrimitive(const std::string &type, const std::string name)
{
    std::string path = "./plugins/lib" + type + "Primitive.so";

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::IPrimitive>>(path);
        Raytracer::IPrimitive* getEntryPoint = loader->getInstance("entryPoint");

        if (!getEntryPoint) {
            throw ErrorException("EntryPoint returned nullptr for " + type);
        }
        std::shared_ptr<Raytracer::IPrimitive> newPrimitive(getEntryPoint);
        newPrimitive->setName(name);
        _primitiveLoader.push_back(std::move(loader));

        return newPrimitive;
    } catch (const std::exception &e) {
        throw ErrorException("Failed to load plugin " + type + ": " + e.what());
    }
}

std::shared_ptr<Raytracer::ILight> Raytracer::ObjectFactory::createLight(const std::string &type, const std::string name)
{
    std::string path = "./plugins/lib" + type + "Light.so";

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::ILight>>(path);
        Raytracer::ILight* getEntryPoint = loader->getInstance("entryPoint");

        if (!getEntryPoint) {
            throw ErrorException("EntryPoint returned nullptr for " + type);
        }
        std::shared_ptr<Raytracer::ILight> newLight(getEntryPoint);
        newLight->setName(name);
        _lightLoader.push_back(std::move(loader));

        return newLight;
    } catch (const std::exception &e) {
        throw ErrorException("Failed to load plugin " + type + ":" + e.what());
    }
}
