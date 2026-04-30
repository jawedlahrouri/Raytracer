/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Object Factory
*/

#ifndef OBJECTFACTORY_HPP_
    #define OBJECTFACTORY_HPP_

#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>

#include "interface/IPrimitive.hpp"
#include "interface/ILight.hpp"
#include "exception.hpp"
#include "DLLoader/load_so.hpp"
#include "parsing.hpp"

namespace Raytracer {
    class ObjectFactory {
        private:
            std::vector<std::unique_ptr<DLLoader<Raytracer::IPrimitive>>> _primitiveLoader;
            std::vector<std::unique_ptr<DLLoader<Raytracer::ILight>>> _lightLoader;

        public:
            std::shared_ptr<Raytracer::IPrimitive> createPrimitive(const std::string &type, const Raytracer::Shape &data);
            std::shared_ptr<Raytracer::IPrimitive> createPrimitive(const std::string &type, const Raytracer::Plane &data);
            std::shared_ptr<Raytracer::ILight> createLight(const std::string &type);
    };
}

#endif /* !OBJECTFACTORY_HPP_ */
