/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** material factory
*/

#include "design_pattern/MaterialFactory.hpp"
#include <iostream>

std::shared_ptr<Raytracer::IMaterial> Raytracer::MaterialFactory::createMaterial(const std::string& type)
{
    std::string path = "./plugins/lib" + type + ".so";
    std::map<std::string, double> empty_params;

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::IMaterial>>(path);
        Raytracer::IMaterial* instance = loader->getInstance("entryPoint", empty_params);

        if (!instance) {
            std::cerr << "EntryPoint returned nullptr for material " << type << std::endl;
            return nullptr;
        }
        std::shared_ptr<Raytracer::IMaterial> newMaterial(instance);
        _materialLoaders.push_back(std::move(loader));
        return newMaterial;
    } catch (const std::exception &e) {
        std::cerr << "Material Factory Error: " << e.what() << std::endl;
        return nullptr;
    }
}
std::shared_ptr<Raytracer::IMaterial> Raytracer::MaterialFactory::createMaterialWithParams(
    const std::string& type, 
    const std::map<std::string, double>& params
)
{
    std::string path = "./plugins/lib" + type + ".so";

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::IMaterial>>(path);
        Raytracer::IMaterial* instance = loader->getInstance("entryPoint", params);

        if (!instance) {
            std::cerr << "EntryPoint returned nullptr for material " << type << std::endl;
            return nullptr;
        }
        std::shared_ptr<Raytracer::IMaterial> newMaterial(instance);
        _materialLoaders.push_back(std::move(loader));
        return newMaterial;
    } catch (const std::exception &e) {
        std::cerr << "Material Factory Error: " << e.what() << std::endl;
        return nullptr;
    }
}
