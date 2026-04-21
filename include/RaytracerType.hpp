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

#endif /* !RAYTRACERTYPE_HPP_ */
