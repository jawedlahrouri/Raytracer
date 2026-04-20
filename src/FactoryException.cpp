/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Factory Exception
*/
#include "FactoryException.hpp"

Raytracer::FactoryException::FactoryException(const std::string message) :_message(message)
{
}

const char *Raytracer::FactoryException::what() const noexcept
{
    return _message.c_str();
}
