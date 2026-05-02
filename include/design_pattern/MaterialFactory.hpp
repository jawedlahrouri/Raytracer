#ifndef MATERIAL_FACTORY_HPP_
#define MATERIAL_FACTORY_HPP_

#include <string>
#include <memory>
#include <map>
#include <functional>
#include "interface/IMaterial.hpp"
#include "DLLoader/load_so.hpp"

namespace Raytracer {
    class MaterialFactory {
        public:
            MaterialFactory() = default;
            ~MaterialFactory() = default;
            std::shared_ptr<IMaterial> createMaterial(const std::string& type);
        private:
            std::vector<std::unique_ptr<DLLoader<IMaterial>>> _materialLoaders;
    };
}

#endif /* !MATERIAL_FACTORY_HPP_ */
