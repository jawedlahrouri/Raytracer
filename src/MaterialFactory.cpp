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

    try {
        auto loader = std::make_unique<DLLoader<Raytracer::IMaterial>>(path);
        Raytracer::IMaterial* instance = loader->getInstance("entryPoint");

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

std::shared_ptr<Raytracer::IMaterial> Raytracer::MaterialFactory::createMaterialWithParams(const std::string& type, const std::map<std::string, double>& params)
{
    std::string path = "./plugins/lib" + type + ".so";

    try {
        if (type == "TransparentMaterial") {
            auto loader = std::make_unique<DLLoader<Raytracer::IMaterial>>(path);
            double opacity = 0.5;
            if (params.find("opacity") != params.end()) {
                opacity = params.at("opacity");
                if (opacity < 0.0) opacity = 0.0;
                if (opacity > 1.0) opacity = 1.0;
            }
            Raytracer::IMaterial* instance = nullptr;
            try {
                instance = loader->getInstance("entryPointWithOpacity", opacity);
            } catch (...) {
                instance = loader->getInstance("entryPoint");
            }
            if (instance) {
                std::shared_ptr<Raytracer::IMaterial> newMaterial(instance);
                _materialLoaders.push_back(std::move(loader));
                return newMaterial;
            }
            return nullptr;
        } else if (type == "ReflectionMaterial") {
            auto loader = std::make_unique<DLLoader<Raytracer::IMaterial>>(path);
            double reflectivity = 0.5;
            if (params.find("reflectivity") != params.end()) {
                reflectivity = params.at("reflectivity");
                if (reflectivity < 0.0) reflectivity = 0.0;
                if (reflectivity > 1.0) reflectivity = 1.0;
            }
            Raytracer::IMaterial* instance = nullptr;
            try {
                instance = loader->getInstance("entryPointWithReflectivity", reflectivity);
            } catch (...) {
                instance = loader->getInstance("entryPoint");
            }
            if (instance) {
                std::shared_ptr<Raytracer::IMaterial> newMaterial(instance);
                _materialLoaders.push_back(std::move(loader));
                return newMaterial;
            }
            return nullptr;
        } else {
            auto loader = std::make_unique<DLLoader<Raytracer::IMaterial>>(path);
            Raytracer::IMaterial* instance = loader->getInstance("entryPoint");
            if (!instance) {
                std::cerr << "EntryPoint returned nullptr for material " << type << std::endl;
                return nullptr;
            }
            std::shared_ptr<Raytracer::IMaterial> newMaterial(instance);
            _materialLoaders.push_back(std::move(loader));
            return newMaterial;
        }
    } catch (const std::exception &e) {
        std::cerr << "Material Factory Error: " << e.what() << std::endl;
        return nullptr;
    }
}
