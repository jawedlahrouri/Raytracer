/*
** EPITECH PROJECT, 2026
** RaytracerType
** File description:
** enum and structs for all the project
*/

#ifndef RAYTRACERTYPE_HPP_
#define RAYTRACERTYPE_HPP_

namespace Raytracer {
    enum coordType {
        NONE,
        x,
        y,
        z,
    };

    enum specsType {
        NONE,
        r,
        width,
        height,
        length,
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
        X,
        Y,
        Z,
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
