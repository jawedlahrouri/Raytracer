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
    cam.size =  {
        _config["Camera"]["resolution"][0].get<int>(),
        _config["Camera"]["resolution"][1].get<int>(),
    };

    // position parsing
    cam.posCoords = {
        {Raytracer::coordType::x, _config["Camera"]["position"][0].get<float>()},
        {Raytracer::coordType::y, _config["Camera"]["position"][1].get<float>()},
        {Raytracer::coordType::z, _config["Camera"]["position"][2].get<float>()},
    };

    // rotation parsing
    cam.rotaCoords = {
        {Raytracer::coordType::x, _config["Camera"]["rotation"][0].get<float>()},
        {Raytracer::coordType::y, _config["Camera"]["rotation"][1].get<float>()},
        {Raytracer::coordType::z, _config["Camera"]["rotation"][3].get<float>()},
    };

    // field of view parsing
    cam.fieldOfView = _config["Camera"]["fieldOfView"].get<float>();
    _camera = cam;
}

void Raytracer::Parser::parsePrimitive()
{
    Raytracer::Primitive prim;
    int id_plane = 0;
    
    // Shape parsing and plane
    for (int i = 0; i <= _config["Primitives"].size(); i++) {
        std::string type = _config["Primitives"][i]["type"].get<std::string>();
        if (type != "Plane") {
            Raytracer::Shape shape;

            // name of the shape
            shape.shapeName = type;
            
            // coords of the shape
            shape.coords = {
                {Raytracer::coordType::x, _config["Primitives"][i]["coords"][0].get<float>()},
                {Raytracer::coordType::y, _config["Primitives"][i]["coords"][1].get<float>()},
                {Raytracer::coordType::z, _config["Primitives"][i]["coords"][2].get<float>()},
            };

            // specifications of the shape
            auto& specs_json = _config["Primitives"][i]["specification"];
            if (!specs_json[0].isNull())
                shape.specs[Raytracer::specsType::r] = specs_json[0].get<float>();
            if (!specs_json[1].isNull())
                shape.specs[Raytracer::specsType::width] = specs_json[1].get<float>();
            if (!specs_json[2].isNull())
                shape.specs[Raytracer::specsType::height] = specs_json[2].get<float>();
            if (!specs_json[3].isNull())
                shape.specs[Raytracer::specsType::length] = specs_json[3].get<float>();

            // color of the shape
            shape.color = {
                {Raytracer::colorType::RED, _config["Primitives"][i]["color"][0].get<std::size_t>()},
                {Raytracer::colorType::GREEN, _config["Primitives"][i]["color"][1].get<std::size_t>()},
                {Raytracer::colorType::BLUE, _config["Primitives"][i]["color"][2].get<std::size_t>()},
            };

            _primitive.listOfShapes[type] = shape;
        }
        else {
            Raytracer::Plane floor;

            // get the axis
            std::string axe = _config["Primitives"][i]["axis"].get<std::string>();
            if (axe == "X")
                floor.axis == Raytracer::planesType::X;
            else if (axe == "Y")
                floor.axis == Raytracer::planesType::Y;
            else
                floor.axis == Raytracer::planesType::Z;
            
            // get the position
            float pos = _config["Primitives"][i]["position"].get<float>();
            floor.positions = pos;

            // get the color
            floor.color = {
                {Raytracer::colorType::RED, _config["Primitives"][i]["color"][0].get<std::size_t>()},
                {Raytracer::colorType::GREEN, _config["Primitives"][i]["color"][1].get<std::size_t>()},
                {Raytracer::colorType::BLUE, _config["Primitives"][i]["color"][2].get<std::size_t>()},
            };

            _primitive.listOfPlane[id_plane] = floor;
            id_plane++;
        }
    }
}

void Raytracer::Parser::parseLight()
{
    Raytracer::Lights light;
    light.lightParams = {
        {Raytracer::lightsType::ambient, _config["Lights"]["ambient"].get<float>()},
        {Raytracer::lightsType::diffuse, _config["Lights"]["diffuse"].get<float>()},
    };

    for (int i = 0; i <= _config["Lights"]["point"].size(); i++) {
        // vector  
    }
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