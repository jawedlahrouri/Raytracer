#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "RaytracerType.hpp"

namespace Raytracer {
    struct Camera {
        std::pair<size_t, std::size_t> size;
        std::map<enum Raytracer::valuesType, int> posCoords; // enum values (x, y, z)
        std::map<enum Raytracer::valuesType, int> rotaCoords; //  enum values (x, y, z) (on peut changer zehma c chaud)
        size_t fieldOfView; // in degree
    };

    struct Shape {
        std::string shapeName;
        std::map<enum Raytracer::valuesType, std::size_t> coords; // enum values (x, y, z) or more (ex: r for radius for sphere)
        std::map<enum Raytracer::colorType, std::size_t> color; // RED, GREEN, BLUE
    };

    struct Plane {
        std::map<enum Raytracer::planesType, std::size_t> localisation;
        std::map<enum Raytracer::colorType, int> color; // RED, GREEN, BLUE
    };

    struct Primitive {
        std::map<enum Raytracer::shapesType, Shape> listOfShapes; // sphere, cube, ect
        std::map<enum Raytracer::planesType, Plane> listOfPlane; // axis, position
    };

    struct Lights {
        std::map<enum Raytracer::lightsType, std::size_t> lightParams; // ambient and diffuse
        std::map<std::string, Raytracer::point> listPoints;
        std::map<std::string, Raytracer::vectorLight> listDirectional;
    };
}

namespace Raytracer {
    class Parser {
        private:
            std::string _filename;
            Raytracer::Camera camera;
            Raytracer::Primitive primitive;
            Raytracer::Lights Lights;

        public:
            Parser(std::string filename);
            ~Parser();

            Raytracer::Camera getInfoCamera();
            Raytracer::Primitive getInfoPrimitive();
            Raytracer::Lights getInfoLights();
    };
}