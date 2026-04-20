/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Factory Exception
*/

#ifndef FACTORYEXCEPTION_HPP_
    #define FACTORYEXCEPTION_HPP_

#include <iostream>
#include <exception>

namespace Raytracer {
    class FactoryException : public std::exception {
        private:
            std::string _message;

        public:
            explicit FactoryException(const std::string message);
            const char*what() const noexcept override;
    };
}

#endif /* !FACTORYEXCEPTION_HPP_ */
