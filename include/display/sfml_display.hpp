/*
** EPITECH PROJECT, 2026
** Raytracer-1
** File description:
** sfml_display.hpp
*/

#ifndef SFML_DISPLAY_HPP_
    #define SFML_DISPLAY_HPP_

#include <SFML/Graphics.hpp>
#include "math/Vector3D.hpp"

namespace Raytracer {
    class SfmlDisplay {
        public:
            SfmlDisplay(int width, int height, std::string name);
            ~SfmlDisplay();
            void updatePixel(int x, int y, const Math::Vector3D& color);
            void refresh();
            bool isOpen() const;
            void display(const std::vector<std::vector<Math::Vector3D>>& pixels);
    private:
        int _width;
        int _height;
        std::string _name;
        sf::RenderWindow _window;
        sf::Image _image;
        sf::Texture _texture;
        sf::Sprite _sprite;
    };
}

#endif /* !SFML_DISPLAY_HPP_ */
