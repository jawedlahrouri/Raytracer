#ifndef MATERIAL_FACTORY_HPP_
#define MATERIAL_FACTORY_HPP_

#include <string>
#include <memory>
#include <map>
#include <functional>
#include "interface/IMaterial.hpp"

namespace Raytracer {
    class MaterialFactory {
        public:
            MaterialFactory();
            ~MaterialFactory() = default;
            std::shared_ptr<IMaterial> createMaterial(const std::string& type);
        private:
            std::map<std::string, std::function<std::shared_ptr<IMaterial>()>> _materialMap;
    };
}

#endif /* !MATERIAL_FACTORY_HPP_ */