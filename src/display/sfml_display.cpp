/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** sfml_display.cpp
*/

#include "display/sfml_display.hpp"

namespace Raytracer {

    Raytracer::SfmlDisplay::SfmlDisplay(int width, int height, std::string name)
        : _width(width), _height(height), _name(name),
          _window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), name)
    {
        _image.create(static_cast<unsigned int>(_width), static_cast<unsigned int>(_height), sf::Color::Black);
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
    }

    Raytracer::SfmlDisplay::~SfmlDisplay() {
    }

    void Raytracer::SfmlDisplay::updatePixel(int x, int y, const Math::Vector3D& color) {
        if (x < 0 || x >= _width || y < 0 || y >= _height)
            return;
        sf::Color sfColor(
            static_cast<sf::Uint8>(std::min(255.0, std::max(0.0, color.X * 255.0))),
            static_cast<sf::Uint8>(std::min(255.0, std::max(0.0, color.Y * 255.0))),
            static_cast<sf::Uint8>(std::min(255.0, std::max(0.0, color.Z * 255.0)))
        );
        _image.setPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y), sfColor);
    }

    void Raytracer::SfmlDisplay::refresh() {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        if (_window.isOpen()) {
            _texture.loadFromImage(_image);
            _window.clear();
            _window.draw(_sprite);
            _window.display();
        }
    }

    bool Raytracer::SfmlDisplay::isOpen() const {
        return _window.isOpen();
    }

    void Raytracer::SfmlDisplay::display(const std::vector<std::vector<Math::Vector3D>>& pixels) {
        for (int j = 0; j < _height; j++) {
            for (int i = 0; i < _width; i++) {
                updatePixel(i, j, pixels[j][i]);
            }
        }
        while (isOpen()) {
            refresh();
        }
    }
}
