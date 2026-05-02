/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** material factory
*/

#include "design_pattern/MaterialFactory.hpp"
#include "Materials/FlatMaterial.hpp"
#include <memory>
#include <string>

Raytracer::MaterialFactory::MaterialFactory()
{
    _materialMap["FlatMaterial"] = []() { return std::make_shared<Raytracer::FlatMaterial>(); };
}

std::shared_ptr<IMaterial> Raytracer::MaterialFactory::createMaterial(const std::string& type)
{
    auto it = _materialMap.find(type);
    if (it != _materialMap.end())
        return it->second();
    else
        return std::make_shared<Raytracer::FlatMaterial>();
}
