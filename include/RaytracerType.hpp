/*
** EPITECH PROJECT, 2026
** RaytracerType
** File description:
** enum and structs for all the project
*/

#ifndef RAYTRACERTYPE_HPP_
#define RAYTRACERTYPE_HPP_

namespace Raytracer {
    enum valuesType {
        NONE,
        x,
        y,
        z,
        r,
    };

    enum colorType {
        RED,
        GREEN,
        BLUE,
    };

    enum shapesType {
        sphere,
        rect,
        planes,
        // could add some more
    };

    enum planesType {
        axis,
        position,
    };

    enum rectType {
        width,
        height,
    };

    enum sphereType {
        radius,
    };

    enum lightsType {
        ambient,
        diffuse,
    };

    struct point {
        int y;
        int x;
        int z;
    };

    struct vectorLight {
        int y;
        int x;
        int z;
        int direction;
    };
}

struct Color {
    unsigned int r;
    unsigned int g;
    unsigned int b;

    Color() : r(0), g(0), b(0) {}
    Color(unsigned int red, unsigned int green, unsigned int blue) : r(red), g(green), b(blue) {}
};

#endif /* !RAYTRACERTYPE_HPP_ */
