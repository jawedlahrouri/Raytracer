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
#include <memory>
#include <functional>

#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "JsonsInterpreter.hpp"

namespace Raytracer {
    class ObjectFactory {
        private:
            std::unordered_map<std::string, std::function<std::unique_ptr<Raytracer::IPrimitive>(const myjson::JsonValue&)>> _createPrimitive;
            std::unordered_map<std::string, std::function<std::unique_ptr<Raytracer::ILight>(const myjson::JsonValue&)>> _createLight;

        public:
            ObjectFactory();
            std::unique_ptr<Raytracer::IPrimitive> createPrimitive(const std::string &type, const myjson::JsonValue &config);
            std::unique_ptr<Raytracer::ILight> createLight(const std::string &type, const myjson::JsonValue &config);
    };
}

#endif /* !OBJECTFACTORY_HPP_ */
