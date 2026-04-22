/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** load_so
*/

#ifndef LOAD_SO_HPP_
#define LOAD_SO_HPP_
#include <dlfcn.h>
#include <string>
#include "exception.hpp"

    template <typename T>
    class DLLoader {
        private:
            void* _handle;

        public:

        /**
         * @brief Opens a dynamic library handle from a filesystem path.
         * @param path Path to the shared object file.
         * @return Does not return a value.
         */
        DLLoader(const std::string &path) {
            _handle = ::dlopen(path.c_str(), RTLD_LAZY); 
            if (!_handle) {
                throw Exception(::dlerror());
            }
        }

        /**
         * @brief Closes the dynamic library handle if it is open.
         * @return Does not return a value.
         */
        ~DLLoader() {
            if (_handle) {
                ::dlclose(_handle);
            }
        }

        /**
         * @brief Resolves a factory symbol and returns a typed instance.
         * @param symbol Name of the exported factory symbol.
         * @return Pointer to the created instance.
         */
        T* getInstance(const std::string &symbol) {
            ::dlerror();
            void* raw_sym = ::dlsym(_handle, symbol.c_str());
            const char* dlsym_error = ::dlerror();
            
            if (dlsym_error) {
                throw Exception(dlsym_error);
            }
            typedef T* (*CreatorFunc)();
            CreatorFunc creator = reinterpret_cast<CreatorFunc>(raw_sym);
            T* instance = creator();
            return instance;
        }

        /**
         * @brief Resolves and calls a type getter symbol from the loaded library.
         * @brief 0 for primitives, 1 for lights, 2 for materials.
         * @param symbol Name of the exported type symbol.
         * @return Integer identifying the library kind.
         */
        int getType(const std::string &symbol = "getType") {
            ::dlerror();
            void* raw_sym = ::dlsym(_handle, symbol.c_str());
            const char* dlsym_error = ::dlerror();

            if (dlsym_error) {
                throw Exception(dlsym_error);
            }
            typedef int (*TypeGetterFunc)();
            TypeGetterFunc getter = reinterpret_cast<TypeGetterFunc>(raw_sym);
            return getter();
        }
    };

#endif /* !LOAD_SO_HPP_ */