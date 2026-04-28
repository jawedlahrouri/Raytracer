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

#include "IPrimitive.hpp"
#include "ILight.hpp"

namespace Raytracer {
    class ObjectFactory {
        private:
            std::unordered_map<std::string, std::function<std::shared_ptr<Raytracer::IPrimitive>()>> _createPrimitive;
            std::unordered_map<std::string, std::function<std::shared_ptr<Raytracer::ILight>()>> _createLight;
            std::map<std::string, int> _counts;

        public:
            ObjectFactory();
            std::shared_ptr<Raytracer::IPrimitive> createPrimitive(const std::string &type);
            std::shared_ptr<Raytracer::ILight> createLight(const std::string &type);
    };
}

#endif /* !OBJECTFACTORY_HPP_ */
