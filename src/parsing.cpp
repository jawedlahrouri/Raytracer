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

// Parsing function

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
    std::map<enum Raytracer::valuesType, float> position;
    float val = 0;
    for (int i = 0; i <= 2; i++) {
        val = _config["Camera"]["position"][i].get<float>();
        if (i == 0)
            position.insert({Raytracer::valuesType::x, val});
        else if (i == 1)
            position.insert({Raytracer::valuesType::y, val});
        else
            position.insert({Raytracer::valuesType::z, val});
    }
    cam.posCoords = position;

    // rotation parsing
    std::map<enum Raytracer::valuesType, float> rotation;
    for (int i = 0; i <= 2; i++) {
        val = _config["Camera"]["rotation"][i].get<float>();
        if (i == 0)
            rotation.insert({Raytracer::valuesType::x, val});
        else if (i == 1)
            rotation.insert({Raytracer::valuesType::y, val});
        else
            rotation.insert({Raytracer::valuesType::z, val});
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
    // Shape parsing
    std::string name; 
    for (int i = 0; i <= _config["primitives"].size(); i++) {
        // rien
    }

    // test
    int va_test = _config["Primitives"][1]["coords"][1].get<int>();
    std::cout << va_test << std::endl;
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