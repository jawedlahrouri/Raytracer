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
        std::pair<double, double> size;
        Math::Point3D posCoords; // enum values (x, y, z)
        std::map<enum Raytracer::coordType, double> rotaCoords; //  enum values (x, y, z) (on peut changer zehma c chaud)
        size_t fieldOfView; // in degree
    };

    struct Shape {
        std::string shapeName;
        Math::Point3D coords; // enum values (x, y, z)
        std::map<enum Raytracer::specsType, double> specs; // specifications for shape
        Math::Vector3D color; // RED, GREEN, BLUE
    };

    struct Plane {
        Math::Vector3D axis; // axis X, Y or Z
        float positions;
        Math::Vector3D color; // RED, GREEN, BLUE
    };

    struct Primitive {
        std::map<std::string, Shape> listOfShapes; // sphere, cube, ect
        std::map<std::string, Plane> listOfPlane; // axis, position
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
            std::map<std::string, int> typeCounter;

        public:
            Parser(std::string filename);
            ~Parser();

            Raytracer::Camera getInfoCamera();
            Raytracer::Primitive getInfoPrimitive();
            Raytracer::Lights getInfoLights();

            void setInfoCamera(Raytracer::Camera camera);
            void setInfoPrimitive(Raytracer::Primitive primitive);
            void setInfoLights(Raytracer::Lights lights);
            std::string setName(std::string name);

            int parser();
            void parseCamera();
            void parsePrimitive();
            void parseLight();
    };
}

#endif