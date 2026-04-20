/*
** EPITECH PROJECT, 2026
** parsing
** File description:
** Parsing class for parse the config file
*/

#ifndef PARCING_HPP_
#define PARCING_HPP_

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "exception.hpp"
#include "RaytracerType.hpp"
#include "utils/JsonInterpreter.hpp"

namespace Raytracer {
    struct Camera {
        std::pair<size_t, std::size_t> size;
        std::map<enum Raytracer::valuesType, float> posCoords; // enum values (x, y, z)
        std::map<enum Raytracer::valuesType, float> rotaCoords; //  enum values (x, y, z) (on peut changer zehma c chaud)
        size_t fieldOfView; // in degree
    };

    struct Shape {
        std::string shapeName;
        std::map<enum Raytracer::valuesType, std::size_t> coords; // enum values (x, y, z) or more (ex: r for radius for sphere)
        std::map<enum Raytracer::colorType, std::size_t> color; // RED, GREEN, BLUE
    };

    struct Plane {
        std::map<std::string, enum Raytracer::planesType> localisation; // axis X, Y or Z
        std::map<enum Raytracer::colorType, int> color; // RED, GREEN, BLUE
    };

    struct Primitive {
        std::map<enum Raytracer::shapesType, Shape> listOfShapes; // sphere, cube, ect
        std::map<enum Raytracer::planesType, Plane> listOfPlane; // axis, position
    };

    struct Lights {
        std::map<enum Raytracer::lightsType, std::size_t> lightParams; // ambient and diffuse
        std::map<std::string, Raytracer::point> listPoints; // list of differents lights points
        std::map<std::string, Raytracer::vectorLight> listDirectional;
    };
}

namespace Raytracer {
    class Parser {
        private:
            std::string _filename;
            myjson::JsonValue _config;
            Raytracer::Camera _camera;
            Raytracer::Primitive _primitive;
            Raytracer::Lights _lights;

        public:
            Parser(std::string filename);
            ~Parser();

            Raytracer::Camera getInfoCamera();
            Raytracer::Primitive getInfoPrimitive();
            Raytracer::Lights getInfoLights();

            void setInfoCamera(Raytracer::Camera camera);
            void setInfoPrimitive(Raytracer::Primitive primitive);
            void setInfoLights(Raytracer::Lights lights);

            int parser();
            void parseCamera();
            void parsePrimitive();
            void parseLight();
    };
}

#endif