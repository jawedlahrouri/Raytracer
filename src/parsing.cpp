/*
** EPITECH PROJECT, 2026
** Parsing 
** File description:
** Parsing functions for config file
*/

#include "parsing.hpp"

Raytracer::Parser::Parser(std::string filename) : _filename(filename)
{
}

Raytracer::Parser::~Parser()
{
}

// Getter

Raytracer::Camera Raytracer::Parser::getInfoCamera()
{
    return _camera;
}

Raytracer::Primitive Raytracer::Parser::getInfoPrimitive()
{
    return _primitive;
}

Raytracer::Lights Raytracer::Parser::getInfoLights()
{
    return _lights;
}

// Setter

void Raytracer::Parser::setInfoCamera(Raytracer::Camera camera)
{
    _camera = camera;
}

void Raytracer::Parser::setInfoPrimitive(Raytracer::Primitive primitive)
{
    _primitive = primitive;
}

void Raytracer::Parser::setInfoLights(Raytracer::Lights lights)
{
    _lights = lights;
}

void Raytracer::Parser::parseCamera()
{
    Raytracer::Camera cam;
    // resolution parsing
    std::pair<std::size_t, std::size_t> resolution;
    int resOne = _config["Camera"]["resolution"][0].get<int>();
    int resTwo = _config["Camera"]["resolution"][1].get<int>();
    resolution.first = resOne;
    resolution.second = resTwo;
    cam.size = resolution;

    // position parsing
    std::map<enum Raytracer::coordType, float> position;
    float val = 0;
    for (int i = 0; i <= 2; i++) {
        val = _config["Camera"]["position"][i].get<float>();
        if (i == 0)
            position.insert({Raytracer::coordType::x, val});
        else if (i == 1)
            position.insert({Raytracer::coordType::y, val});
        else
            position.insert({Raytracer::coordType::z, val});
    }
    cam.posCoords = position;

    // rotation parsing
    std::map<enum Raytracer::coordType, float> rotation;
    for (int i = 0; i <= 2; i++) {
        val = _config["Camera"]["rotation"][i].get<float>();
        if (i == 0)
            rotation.insert({Raytracer::coordType::x, val});
        else if (i == 1)
            rotation.insert({Raytracer::coordType::y, val});
        else
            rotation.insert({Raytracer::coordType::z, val});
    }
    cam.rotaCoords = rotation;

    // field of view parsing
    float fov = _config["Camera"]["fieldOfView"].get<float>();
    cam.fieldOfView = fov;
    setInfoCamera(cam);
}

void Raytracer::Parser::parsePrimitive()
{
    Raytracer::Primitive prim;
    std::map<enum Raytracer::shapesType, Raytracer::Shape> shapeMap;

    // Shape parsing
    for (int i = 0; i <= _config["Primitives"].size(); i++) {
        Raytracer::Shape shape;

        // name of the shape
        std::string name = _config["Primitives"][i]["type"].get<std::string>();
        shape.shapeName = name;
        
        // coords of the shape
        std::map<Raytracer::coordType, float> coord;
        float val;
        for (int j = 0; j <= 2; j++) {
            val = _config["Primitives"][i]["coords"][j].get<float>();
            if (j == 0)
                coord.insert({Raytracer::coordType::x, val});
            else if (j == 1)
                coord.insert({Raytracer::coordType::y, val});
            else
                coord.insert({Raytracer::coordType::z, val});
        }
        shape.coords = coord;

        // specifications of the shape
        std::map<Raytracer::specsType, float> spec;
        for (int k = 0; k <= _config["Primitives"][i]["specification"].size(); k++) {
            switch (k) {
                case 0 :
                    spec.insert({Raytracer::specsType::r, _config["Primitives"][i]["specification"][k].get<float>()});
                case 1 :
                    spec.insert({Raytracer::specsType::width, _config["Primitives"][i]["specification"][k].get<float>()});
                case 2 :
                    spec.insert({Raytracer::specsType::height, _config["Primitives"][i]["specification"][k].get<float>()});
                case 3 :
                    spec.insert({Raytracer::specsType::length, _config["Primitives"][i]["specification"][k].get<float>()});
            }
        }
        shape.specs = spec;

        // color of the shape
        std::map<Raytracer::colorType, std::size_t> colorMap;
        std::size_t valPixel;
        for (int l = 0; l <= 2; l++) {
            valPixel = _config["Primitives"][i]["color"][l].get<std::size_t>();
            if (l == 0)
                colorMap.insert({Raytracer::colorType::RED, valPixel});
            else if (l == 1)
                colorMap.insert({Raytracer::colorType::GREEN, valPixel});
            else
                colorMap.insert({Raytracer::colorType::BLUE, valPixel});
        }
        shape.color = colorMap; 
    }
}

void Raytracer::Parser::parseLight()
{
    
}

int Raytracer::Parser::parser()
{
    try {
        _config = myjson::parseFile(_filename);
        parseCamera();
        parsePrimitive();

    } catch (std::exception &e) {
        std::cerr << "Parsing Exception : " << e.what() << std::endl;
        return 84;
    }

    return 0;
}