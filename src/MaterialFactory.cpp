/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** material factory
*/

#include "design_pattern/MaterialFactory.hpp"
#include <iostream>

std::shared_ptr<IMaterial> Raytracer::MaterialFactory::createMaterial(const std::string& type)
{
    std::string path = "./plugins/lib" + type + ".so";

    try {
        auto loader = std::make_unique<DLLoader<IMaterial>>(path);
        IMaterial* instance = loader->getInstance("entryPoint");

        if (!instance) {
            std::cerr << "EntryPoint returned nullptr for material " << type << std::endl;
            return nullptr;
        }
        std::shared_ptr<IMaterial> newMaterial(instance);
        _materialLoaders.push_back(std::move(loader));
        return newMaterial;
    } catch (const std::exception &e) {
        std::cerr << "Material Factory Error: " << e.what() << std::endl;
        return nullptr;
    }
}
