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
#include "math/Point3D.hpp"
#include "exception.hpp"
#include "RaytracerType.hpp"
#include "utils/JsonInterpreter.hpp"

namespace Raytracer {
    struct Camera {
        std::pair<size_t, std::size_t> size;
        std::map<enum Raytracer::coordType, float> posCoords; // enum values (x, y, z)
        std::map<enum Raytracer::coordType, float> rotaCoords; //  enum values (x, y, z) (on peut changer zehma c chaud)
        size_t fieldOfView; // in degree
    };

    struct Shape {
        std::string shapeName;
        std::map<enum Raytracer::coordType, float> coords; // enum values (x, y, z)
        std::map<enum Raytracer::specsType, float> specs; // specifications for shape
        std::map<enum Raytracer::colorType, std::size_t> color; // RED, GREEN, BLUE
    };

    struct Plane {
        enum Raytracer::planesType axis; // axis X, Y or Z
        float positions;
        std::map<enum Raytracer::colorType, std::size_t> color; // RED, GREEN, BLUE
    };

    struct Primitive {
        std::map<std::string, Shape> listOfShapes; // sphere, cube, ect
        std::map<unsigned int, Plane> listOfPlane; // axis, position
    };

    struct Lights {
        std::map<enum Raytracer::lightsType, std::size_t> lightParams; // ambient and diffuse
        std::map<unsigned int, Math::Point3D> listPoints; // list of differents lights points
        std::map<unsigned int, Math::Vector3D> listDirectional;
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