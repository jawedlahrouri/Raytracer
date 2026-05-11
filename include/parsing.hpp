/*
** EPITECH PROJECT, 2026
** parsing
** File description:
** Parsing class for parse the config file
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"
#include "exception.hpp"
#include "RaytracerType.hpp"
#include "utils/JsonInterpreter.hpp"

namespace Raytracer {
    struct Camera {
        std::pair<double, double> size;
        Math::Point3D posCoords;
        std::map<enum Raytracer::coordType, double> rotaCoords;
        size_t fieldOfView;
    };

    struct Light {
        Math::Point3D position;
        Math::Vector3D direction;
        Math::Vector3D lightColor;
        Raytracer::colorType intensity;
        float ambientIntensity;
    };

    struct Shape {
        std::string type;
        std::string shapeName;
        Math::Point3D coords;
        Math::Vector3D rotation;
        double scale;
        std::map<enum Raytracer::specsType, double> specs;
        Math::Vector3D color;
        std::string material;
        std::map<std::string, double> materialParams;
    };

    struct Plane {
        Math::Vector3D axis;
        float positions;
        Math::Vector3D rotation;
        Math::Vector3D color;
        std::string material;
        std::map<std::string, double> materialParams;
    };

    struct Primitive {
        std::map<std::string, Shape> listOfShapes;
        std::map<std::string, Plane> listOfPlane;
    };

    struct Lights {
        std::map<enum Raytracer::lightsType, float> lightParams;
        std::map<unsigned int, Math::Point3D> listPoints;
        std::map<unsigned int, Math::Vector3D> listDirectional;
        std::map<unsigned int, std::pair<Math::Point3D, Math::Vector3D>> listColored;
    };

    class Parser {
        private:
            std::string _filename;
            myjson::JsonValue _config;
            Camera _camera;
            Primitive _primitive;
            Lights _lights;
            std::map<std::string, int> typeCounter;

        public:
            Parser(std::string filename);
            ~Parser();

            Camera getInfoCamera();
            Primitive getInfoPrimitive();
            Lights getInfoLights();

            void setInfoCamera(Camera camera);
            void setInfoPrimitive(Primitive primitive);
            void setInfoLights(Lights lights);
            std::string setName(std::string name);

            int parser();
            void parseCamera();
            void parsePrimitive();
            void parseLight();
    };
}

#endif /* !PARSING_HPP_ */
