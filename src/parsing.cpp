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
    if (_config["Camera"]["resolution"].isNull() || _config["Camera"]["resolution"].size() < 2) {
            throw ErrorException("Camera resolution est invalide ou incomplet.");
    }

    cam.size =  {
        _config["Camera"]["resolution"][0].get<double>(),
        _config["Camera"]["resolution"][1].get<double>(),
    };

    // position parsing
    if (_config["Camera"]["position"].isNull() || _config["Camera"]["position"].size() < 3) {
        throw ErrorException("Camera position est invalide ou incomplet.");
    }

    cam.posCoords = {
        _config["Camera"]["position"][0].get<double>(),
        _config["Camera"]["position"][1].get<double>(),
        _config["Camera"]["position"][2].get<double>(),
    };

    // rotation parsing
    if (_config["Camera"]["rotation"].isNull() || _config["Camera"]["rotation"].size() < 3) {
            throw ErrorException("Camera rotation est invalide ou incomplet.");
    }

    cam.rotaCoords = {
        {Raytracer::coordType::x, _config["Camera"]["rotation"][0].get<double>()},
        {Raytracer::coordType::y, _config["Camera"]["rotation"][1].get<double>()},
        {Raytracer::coordType::z, _config["Camera"]["rotation"][2].get<double>()},
    };

    // field of view parsing
    cam.fieldOfView = _config["Camera"]["fieldOfView"].get<double>();
    if (cam.fieldOfView > 180)
        throw ErrorException("Le champ de vision est trop grand");
    _camera = cam;
}

std::string Raytracer::Parser::setName(std::string name)
{
    int currentCount = typeCounter[name]; 
    std::string newName = name + "_" + std::to_string(currentCount);
    
    typeCounter[name]++; 
    
    return newName;
}

void Raytracer::Parser::parsePrimitive()
{
    int id_plane = 0;
    
    // Shape parsing and plane
    for (std::size_t i = 0; i < _config["Primitives"].size(); i++) {
        std::string type = _config["Primitives"][i]["type"].get<std::string>();
        if (type != "Plane") {
            Raytracer::Shape shape;
            shape.type = type;

            // name of the shape
            shape.shapeName = setName(type);
            
            // coords of the shape
            if (_config["Primitives"][i]["coords"].isNull() || _config["Primitives"][i]["coords"].size() < 3) {
                throw ErrorException("Primitives position est invalide ou incomplet.");
            }
            shape.coords = {
                _config["Primitives"][i]["coords"][0].get<float>(),
                _config["Primitives"][i]["coords"][1].get<float>(),
                _config["Primitives"][i]["coords"][2].get<float>(),
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
            if (_config["Primitives"][i]["color"].isNull() || _config["Primitives"][i]["color"].size() < 3) {
                throw ErrorException("Primitives color est invalide ou incomplet.");
            }
            
            shape.color = {
                _config["Primitives"][i]["color"][0].get<double>(),
                _config["Primitives"][i]["color"][1].get<double>(),
                _config["Primitives"][i]["color"][2].get<double>(),
            };
            if (!_config["Primitives"][i]["materials"].isNull())
                shape.material = _config["Primitives"][i]["materials"].get<std::string>();
            else
                shape.material = "FlatMaterial";
            if (!_config["Primitives"][i]["materialParams"].isNull()) {
                auto& params = _config["Primitives"][i]["materialParams"];
                if (!params["opacity"].isNull()) {
                    shape.materialParams["opacity"] = params["opacity"].get<double>();
                }
            }

            if (!_config["Primitives"][i]["scale"].isNull())
                shape.scale = _config["Primitives"][i]["scale"].get<double>();
            else
                shape.scale = 1.0;
            
            _primitive.listOfShapes[shape.shapeName] = shape;
        }
        else {
            Raytracer::Plane floor;
            std::string name;

            name = "Plane_" + std::to_string(id_plane);

            // get the axis
            floor.axis = {
                _config["Primitives"][i]["axis"][0].get<double>(),
                _config["Primitives"][i]["axis"][1].get<double>(),
                _config["Primitives"][i]["axis"][2].get<double>()
            };
            // get the position
            double pos = _config["Primitives"][i]["position"].get<double>();
            floor.positions = pos;

            // get the color
            if (_config["Primitives"][i]["color"].isNull() || _config["Primitives"][i]["color"].size() < 3) {
                throw ErrorException("Primitives color est invalide ou incomplet.");
            }
        
            floor.color = {
                _config["Primitives"][i]["color"][0].get<double>(),
                _config["Primitives"][i]["color"][1].get<double>(),
                _config["Primitives"][i]["color"][2].get<double>(),
            };
            if (!_config["Primitives"][i]["materials"].isNull())
                floor.material = _config["Primitives"][i]["materials"].get<std::string>();
            else
                floor.material = "FlatMaterial";
            if (!_config["Primitives"][i]["materialParams"].isNull()) {
                auto& params = _config["Primitives"][i]["materialParams"];
                if (!params["opacity"].isNull()) {
                    floor.materialParams["opacity"] = params["opacity"].get<double>();
                }
            }
            
            _primitive.listOfPlane[name] = floor;
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

    if (!_config["Lights"]["point"].isNull()) {
        unsigned int id_point = 0;
        for (std::size_t i = 0; i < _config["Lights"]["point"].size(); i++) {
            if (_config["Lights"]["point"][i].isNull() || _config["Lights"]["point"][i].size() < 3)
                throw ErrorException("Light point est invalide ou incomplet.");
            Math::Point3D point = {_config["Lights"]["point"][i][0].get<double>(), _config["Lights"]["point"][i][1].get<double>(), _config["Lights"]["point"][i][2].get<double>()};
            light.listPoints[id_point] = point;
            id_point++;
        }
    }

    if (!_config["Lights"]["directional"].isNull()) {
        unsigned int id_vector = 0;
        for (std::size_t j = 0; j < _config["Lights"]["directional"].size(); j++) {
            if (_config["Lights"]["directional"][j].isNull() || _config["Lights"]["directional"][j].size() < 3)
                throw ErrorException("Light directional est invalide ou incomplet.");
            Math::Vector3D vector = {_config["Lights"]["directional"][j][0].get<double>(), _config["Lights"]["directional"][j][1].get<double>(), _config["Lights"]["directional"][j][2].get<double>()};
            light.listDirectional[id_vector] = vector;
            id_vector++;
        }
    }

    if (!_config["Lights"]["colored"].isNull()) {
        unsigned int id = 0;
        for (std::size_t i = 0; i < _config["Lights"]["colored"].size(); i++) {
            const myjson::JsonValue entry = _config["Lights"]["colored"][i];
            Math::Point3D pos = {entry["position"][0].get<double>(), entry["position"][1].get<double>(),entry["position"][2].get<double>()};
            Math::Vector3D color = {entry["color"][0].get<double>(), entry["color"][1].get<double>(), entry["color"][2].get<double>()};
            light.listColored[id] = {pos, color};
            id++;
        }
    }
    _lights = light;
}

int Raytracer::Parser::parser()
{
    try {
        _config = myjson::parseFile(_filename);
        parseCamera();
        parsePrimitive();
        parseLight();
    } catch (std::exception &e) {
        std::cerr << "Parsing Exception : " << e.what() << std::endl;
        return 84;
    }

    return 0;
}